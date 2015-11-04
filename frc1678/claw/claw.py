import numpy

class Claw():
  def __init__(self, name="Claw", mass=None):
    # Stall Torque in N m
    self.stall_torque = 0.476
    # Stall Current in Amps
    self.stall_current = 80.730
    # Free Speed in RPM
    self.free_speed = 13906.0
    # Free Current in Amps
    self.free_current = 5.820
    # Mass of the claw
    if mass is None:
      self.mass = 5.0
    else:
      self.mass = mass

    # Resistance of the motor
    self.R = 12.0 / self.stall_current
    # Motor velocity constant
    self.Kv = ((self.free_speed / 60.0 * 2.0 * numpy.pi) /
               (12.0 - self.R * self.free_current))
    # Torque constant
    self.Kt = self.stall_torque / self.stall_current
    # Gear ratio
    self.G = (56.0 / 12.0) * (54.0 / 14.0) * (64.0 / 14.0) * (72.0 / 18.0)
    # Claw length
    self.r = 18 * 0.0254

    self.J = self.r * self.mass

    # Control loop time step
    self.dt = 0.005

    # State is [position, velocity]
    # Input is [Voltage]

    C1 = self.G * self.G * self.Kt / (self.R  * self.J * self.Kv)
    C2 = self.Kt * self.G / (self.J * self.R)

    self.A_continuous = numpy.matrix(
        [[0, 1],
         [0, -C1]])

    # Start with the unmodified input
    self.B_continuous = numpy.matrix(
        [[0],
         [C2]])

    self.C = numpy.matrix([[1, 0]])
    self.D = numpy.matrix([[0]])

claw = Claw();
print(claw.A_continuous)
