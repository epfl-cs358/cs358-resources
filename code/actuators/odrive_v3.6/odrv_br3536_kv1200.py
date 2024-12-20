#~/Library/Python/3.8/bin/odrivetool

odrv0.erase_configuration()

#odrv0.config.enable_brake_resistor = True
odrv0.config.brake_resistance = 2
odrv0.config.dc_max_positive_current = 18
odrv0.config.dc_bus_undervoltage_trip_level = 8.0
odrv0.config.dc_bus_overvoltage_trip_level = 56.0
odrv0.config.dc_max_positive_current = 18
odrv0.config.dc_max_negative_current = -3.0
odrv0.config.max_regen_current = 0
odrv0.save_configuration()

odrv0.axis0.motor.config.pole_pairs = 7
odrv0.axis0.motor.config.torque_constant = 8.27 / 1200
odrv0.axis0.motor.config.current_lim = 15
odrv0.axis0.motor.config.calibration_current = 15 
odrv0.axis0.motor.config.resistance_calib_max_voltage = 2
odrv0.axis0.motor.config.motor_type = MOTOR_TYPE_HIGH_CURRENT
odrv0.axis0.motor.config.requested_current_range = 20
#odrv0.axis0.encoder.config.mode = ENCODER_MODE_INCREMENTAL
odrv0.axis0.encoder.config.cpr = 8192
#odrv0.axis0.encoder.config.bandwidth = 3000
odrv0.axis0.config.calibration_lockin.current = 15
#odrv0.axis0.config.calibration_lockin.ramp_distance = 3.1415927410125732
#odrv0.axis0.config.calibration_lockin.accel = 20
#odrv0.axis0.config.calibration_lockin.vel = 40
odrv0.save_configuration()

odrv0.axis0.controller.config.control_mode = CONTROL_MODE_POSITION_CONTROL
odrv0.axis0.controller.config.vel_limit = 50
odrv0.axis0.controller.config.pos_gain = 30
odrv0.axis0.controller.config.vel_gain = 0.008 # MB recommends 0.02
odrv0.axis0.controller.config.vel_integrator_gain = 0.05 # MB recommends 0.2
odrv0.axis0.controller.config.input_mode = INPUT_MODE_TRAP_TRAJ
odrv0.axis0.trap_traj.config.vel_limit = 30
odrv0.axis0.trap_traj.config.accel_limit = 5
odrv0.axis0.trap_traj.config.decel_limit = 5
odrv0.save_configuration()
odrv0.reboot()


odrv0.axis0.requested_state = AXIS_STATE_MOTOR_CALIBRATION
#wait until finished before issuing more commands


# depends on motor, numbers set by motor calibration
#odrv0.axis0.motor.config.phase_inductance = 3.004827931363252e-06
#odrv0.axis0.motor.config.phase_resistance = 0.02507280930876732

odrv0.axis0.motor.config.pre_calibrated = True
odrv0.save_configuration()




odrv0.axis0.requested_state = AXIS_STATE_ENCODER_OFFSET_CALIBRATION
#wait until finished before issuing more commands


odrv0.axis0.requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL

odrv0.axis0.config.startup_encoder_offset_calibration = True
#odrv0.axis0.config.startup_encoder_offset_calibration = False
odrv0.axis0.config.startup_closed_loop_control = False
#odrv0.axis0.config.startup_closed_loop_control = True
odrv0.axis0.encoder.config.use_index = False
odrv0.save_configuration()
odrv0.reboot()


# not in the MakerBase video:
#odrv0.axis0.config.startup_encoder_index_search = True
odrv0.axis0.config.startup_encoder_index_search = False
#odrv0.axis0.encoder.config.use_index = True
odrv0.axis0.encoder.config.use_index = False
odrv0.axis0.encoder.config.pre_calibrated = False
#odrv0.axis0.encoder.config.pre_calibrated = True
odrv0.save_configuration()
odrv0.reboot()


odrv0.axis0.encoder.index_found



odrv0.axis0.requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL


odrv0.axis0.controller.input_pos = 1

odrv0.axis0.requested_state = AXIS_STATE_IDLE


