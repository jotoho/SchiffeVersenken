# Changelog of SchiffeVersenken
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [UNRELEASED]

Full git log:
https://github.com/jotoho/SchiffeVersenken/compare/1.1.0...master

### Fixes
 -  Corrected wrong magnitude of a bitshift. This caused compilation failures on Windows but had no
    impact on x86-64 Linux systems. (Windows is still unsupported)

### Notable
Since the last version, there were a lot of

## [1.1.0] - 2022-02-05

Full git log:
https://github.com/jotoho/SchiffeVersenken/compare/1.0.0...1.1.0

### Added
 -  Added scoreboard of remaining ship parts for each player above the game board

### Changed
 -  The release version is now automatically read from the git repository on build
    and no longer needs to be hardcoded.
 -  Game board generation is now done asynchronously while the user is on the tutorial screen.
    This should make starting the game slightly quicker on systems with multiple threads.

## [1.0.0] - 2022-01-09

Full git log:
https://github.com/jotoho/SchiffeVersenken/compare/1.0.0-rc1...1.0.0

This is the version we submitted for grading. (This was created as a university assignment after all)

<!-- TODO: Add log for this version -->

## [1.0.0-rc1]

Full git log:
https://github.com/jotoho/SchiffeVersenken/compare/0.1.0-alpha...1.0.0-rc1

<!-- TODO: Add log for this version -->

## [0.1.0-alpha] - 2022-01-07

Full git log:
https://github.com/jotoho/SchiffeVersenken/compare/b4834489049013f7fbb84dc333dae4be6a8f4c7d...0.1.0-alpha

This is the oldest tag in the repository.
No changelog can be made for this version.
