# motorThorLabs Releases

## __R1-0-2 (2023-04-13)__
R1-0-2 is a release based on the master branch.

### Changes since R1-0-1

#### New features
* Pull request [#4](https://github.com/epics-motor/motorThorLabs/pull/4): [Keenan Lang](https://github.com/keenanlang) added Kinesis support (KDC101 and KST101)

#### Modifications to existing features
* None

#### Bug fixes
* None

#### Continuous integration
* Added ci-scripts (v3.0.1)
* Configured to use Github Actions for CI

## __R1-0-1 (2020-05-12)__
R1-0-1 is a release based on the master branch.  

### Changes since R1-0

#### New features
* None

#### Modifications to existing features
* None

#### Bug fixes
* Commit [8a1b9cb](https://github.com/epics-motor/motorThorLabs/commit/9ec46c1b328227e3405730bb20f869c8a639cc8e): Include ``$(MOTOR)/modules/RELEASE.$(EPICS_HOST_ARCH).local`` instead of ``$(MOTOR)/configure/RELEASE``
* Pull request [#1](https://github.com/epics-motor/motorThorLabs/pull/1): Eliminated compiler warnings

## __R1-0 (2019-04-18)__
R1-0 is a release based on the master branch.  

### Changes since motor-6-11

motorThorLabs is now a standalone module, as well as a submodule of [motor](https://github.com/epics-modules/motor)

#### New features
* motorThorLabs can be built outside of the motor directory
* motorThorLabs has a dedicated example IOC that can be built outside of motorThorLabs

#### Modifications to existing features
* None

#### Bug fixes
* None
