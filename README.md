# motorThorLabs
EPICS motor drivers for the following [Thorlabs](https://www.thorlabs.com/) controllers: Piezo Controller Model MDT695, Kinesis KDC101 and KST101 (Windows).

[![Build Status](https://github.com/epics-motor/motorThorLabs/actions/workflows/ci-scripts-build.yml/badge.svg)](https://github.com/epics-motor/motorThorLabs/actions/workflows/ci-scripts-build.yml)
<!--[![Build Status](https://travis-ci.org/epics-motor/motorThorLabs.png)](https://travis-ci.org/epics-motor/motorThorLabs)-->

motorThorLabs is a submodule of [motor](https://github.com/epics-modules/motor).  When motorThorLabs is built in the ``motor/modules`` directory, no manual configuration is needed.

motorThorLabs can also be built outside of motor by copying it's ``EXAMPLE_RELEASE.local`` file to ``RELEASE.local`` and defining the paths to ``MOTOR`` and itself.

motorThorLabs contains an example IOC that is built if ``CONFIG_SITE.local`` sets ``BUILD_IOCS = YES``.  The example IOC can be built outside of driver module.
