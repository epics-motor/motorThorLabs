
# KinesisControllerConfig ("PORT NAME", "SERIAL NUMBER", "MOTOR TYPE", moving poll period, idle poll period)
KinesisControllerConfig("KST-01", "0123456", "Stepper", 500, 1000)
KinesisControllerConfig("KDC-01", "0123456", "DC", 500, 1000)

dbLoadTemplate("KCube.substitutions")
