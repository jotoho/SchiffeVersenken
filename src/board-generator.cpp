#include <algorithm>
#include <random>
#include <vector>
#include "../include/fieldinfo.hpp"

using BoardPointRange = std::vector<BoardPoint>;
enum class CardinalDirection : std::uint_least8_t { NORTH, EAST, SOUTH, WEST };

constexpr BoardType generateGameBoardEmpty() {
    BoardType board{};
    for (auto& row : board)
        std::fill(row.begin(), row.end(), FieldValue::EMPTY);
    return board;
}

// file-internal function for generating random value of 32-bit length
static std::uint_fast32_t genRandom32bitVal() {
    // rand() alone doesn't give enough guarantees regarding the size of
    // RAND_MAX for my purposes
    static auto randomNumberGenerator =
        std::minstd_rand{static_cast<unsigned int>(rand())};
    return randomNumberGenerator();
}

// file-internal function for generating random value of 64-bit length
static std::uint_fast64_t genRandom64bitVal() {
    // Fuse two random 32-bit values into one 64-bit uint
    return (genRandom32bitVal() << 32) | genRandom32bitVal();
}

constexpr static bool isInBounds(const std::size_t row,
                                 const std::size_t column) {
    return (row < BoardDimensions.rows) && (column < BoardDimensions.columns);
}

static FieldValue& getRefFromPoint(BoardType& board, const BoardPoint& point) {
    return board[point.x][point.y];
}

static BoardPoint stepsFromPoint(const BoardPoint& originPoint,
                                 const CardinalDirection direction,
                                 const std::size_t numberOfSteps) {
    switch (direction) {
        case CardinalDirection::NORTH:
            return originPoint - BoardPoint{0, numberOfSteps};
        case CardinalDirection::EAST:
            return originPoint + BoardPoint{numberOfSteps, 0};
        case CardinalDirection::SOUTH:
            return originPoint + BoardPoint{0, numberOfSteps};
        case CardinalDirection::WEST:
            return originPoint - BoardPoint{numberOfSteps, 0};
        default:
            throw std::invalid_argument{"Invalid direction was provided"};
    }
}

static void attemptPlacingPlaceholder(BoardType& board,
                                      const BoardPoint& center,
                                      const CardinalDirection direction) {
    try {
        const auto adjacentPoint = stepsFromPoint(center, direction, 1);
        auto& adjacentPointValue = getRefFromPoint(board, adjacentPoint);
        if (adjacentPointValue == FieldValue::EMPTY)
            adjacentPointValue = FieldValue::PLACEHOLDER;
    } catch (const std::exception& ignored) {
    }
}

static bool isThisAreaOnBoardEmpty(const BoardType& board,
                                   const BoardPointRange& points) {
    for (const auto& point : points)
        if (board[point.x][point.y] != FieldValue::EMPTY)
            return false;
    return true;
}

static void writeShipToBoard(BoardType& board,
                             const BoardPointRange& shipPoints) {
    for (const auto& point : shipPoints) {
        getRefFromPoint(board, point) = FieldValue::SHIP;

        // Try placing placeholder in empty slots around ship
        for (const auto directionPlaceholder :
             {CardinalDirection::NORTH, CardinalDirection::EAST,
              CardinalDirection::SOUTH, CardinalDirection::WEST})
            attemptPlacingPlaceholder(board, point, directionPlaceholder);
    }
}

static BoardPoint chooseRandomBoardPoint() {
    return {
        static_cast<std::size_t>(genRandom64bitVal()) % BoardDimensions.columns,
        static_cast<std::size_t>(genRandom64bitVal()) % BoardDimensions.rows};
}

static BoardPointRange generatePointRangeBetween(
    const BoardPoint& startPoint,
    const BoardPoint& endPoint,
    const CardinalDirection direction) {
    BoardPointRange shipPoints;
    shipPoints.emplace_back(startPoint);

    // While list does not contain endPoint
    while (std::find(shipPoints.begin(), shipPoints.end(), endPoint) ==
           shipPoints.end()) {
        const auto lastPoint = shipPoints.at(shipPoints.size() - 1);
        shipPoints.emplace_back(stepsFromPoint(lastPoint, direction, 1));
    }

    return shipPoints;
}

struct InsufficientBoardSpaceError : std::runtime_error {
    InsufficientBoardSpaceError(const std::string msg)
        : std::runtime_error(msg) {}
};

static void randomlyPlaceShip(BoardType& board, const std::size_t shipLength) {
    // This will repeat until the placement was successful
    constexpr std::uint_fast32_t maxAttempts = 1000;
    bool placementSuccessful = false;

    for (std::uint_fast32_t placementAttempt = 1;
         placementAttempt <= maxAttempts && !placementSuccessful;
         placementAttempt++) {
        const BoardPoint selectedPoint = chooseRandomBoardPoint();
        const CardinalDirection direction =
            static_cast<CardinalDirection>(rand() % 4);

        try {
            const BoardPoint endPoint =
                stepsFromPoint(selectedPoint, direction, shipLength);

            const BoardPointRange shipPoints =
                generatePointRangeBetween(selectedPoint, endPoint, direction);

            // Check if placement is possible
            if (!isThisAreaOnBoardEmpty(board, shipPoints))
                continue;

            // Assume everything checks out and set Fields
            writeShipToBoard(board, shipPoints);

            placementSuccessful = true;

        } catch (const std::invalid_argument& e) {
            continue;
        } catch (const std::range_error& e) {
            continue;
        }
    }

    if (!placementSuccessful)
        throw InsufficientBoardSpaceError{
            ("Not enough space to create a ship with length " +
             std::to_string(shipLength) + " (tried " +
             std::to_string(maxAttempts) + " times)")};
}

static BoardType attemptGeneratingRandomBoard() {
    auto board = generateGameBoardEmpty();
    for (std::size_t shipLength = 2; shipLength < ShipDistribution.size();
         shipLength++) {
        if (ShipDistribution[shipLength] == 0)
            continue;

        for (std::uint_fast8_t shipsPlaced = 0;
             shipsPlaced < ShipDistribution[shipLength]; shipsPlaced++)
            randomlyPlaceShip(board, shipLength);
    }
    return board;
}

BoardType generateGameBoardRandom() {
    constexpr std::uint_least8_t maxFailures = 100;
    std::uint_least8_t failedAttempts = 0;

    while (true) {
        try {
            return attemptGeneratingRandomBoard();
        } catch (const InsufficientBoardSpaceError& unused) {
            if (failedAttempts++ >= maxFailures)
                throw InsufficientBoardSpaceError{
                    "Populating board with desired ships is not possible"};
        }
    }
}
