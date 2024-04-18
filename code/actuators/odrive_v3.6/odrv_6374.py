odrv0.erase_configuration()

odrv0.config.enable_brake_resistor = True
odrv0.config.brake_resistance = 2
odrv0.config.dc_max_positive_current = 18
odrv0.axis0.controller.config.vel_limit = 20
odrv0.axis0.motor.config.pole_pairs = 7
odrv0.axis0.motor.config.torque_constant = 8.27 / 190
odrv0.axis0.motor.config.current_lim = 60
odrv0.axis0.motor.config.calibration_current = 30
odrv0.axis0.config.calibration_lockin.current = 30
odrv0.save_configuration()



# sensorless
odrv0.axis0.controller.config.vel_gain = 0.01
odrv0.axis0.controller.config.vel_integrator_gain = 0.05
odrv0.axis0.controller.config.control_mode = CONTROL_MODE_VELOCITY_CONTROL

odrv0.axis0.motor.config.current_lim = 2 * odrv0.axis0.config.sensorless_ramp.current
odrv0.axis0.sensorless_estimator.config.pm_flux_linkage = 5.51328895422 / (7 * 190)
odrv0.axis0.config.enable_sensorless_mode = True
odrv0.axis0.motor.config.pre_calibrated = True
odrv0.save_configuration()

odrv0.axis0.requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL



# sensored mode

odrv0.axis0.config.enable_sensorless_mode = False

odrv0.axis0.encoder.config.cpr = 8192
odrv0.axis0.requested_state = AXIS_STATE_FULL_CALIBRATION_SEQUENCE
#wait until finished before issuing more commands

odrv0.axis0.encoder.config.use_index = True
odrv0.axis0.requested_state = AXIS_STATE_ENCODER_INDEX_SEARCH
#wait until finished before issuing more commands

odrv0.axis0.requested_state = AXIS_STATE_ENCODER_OFFSET_CALIBRATION
#wait until finished before issuing more commands

odrv0.axis0.encoder.config.pre_calibrated = True
odrv0.axis0.motor.config.pre_calibrated = True
odrv0.axis0.config.startup_encoder_index_search = True
odrv0.save_configuration()


# tuning, was done with 50V

odrv0.axis0.controller.config.vel_integrator_gain = 0
odrv0.axis0.controller.config.vel_gain = 0.33
odrv0.axis0.controller.config.pos_gain = 110
odrv0.axis0.controller.config.vel_integrator_gain = 0.5 * 10 * odrv0.axis0.controller.config.vel_gain
odrv0.axis0.requested_state = AXIS_STATE_IDLE
odrv0.save_configuration()


# defaults
odrv0.axis0.controller.config.vel_integrator_gain = 0
odrv0.axis0.controller.config.vel_gain = 0.16
odrv0.axis0.controller.config.pos_gain = 20
odrv0.axis0.controller.config.vel_integrator_gain = 0.32
odrv0.save_configuration()

odrv0.axis0.requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL
odrv0.axis0.controller.input_pos = 1.5



# filtered position control
odrv0.axis0.controller.config.input_filter_bandwidth = 5
odrv0.axis0.controller.config.input_mode = INPUT_MODE_POS_FILTER
odrv0.axis0.requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL


def goto(x):
  odrv0.axis0.controller.input_pos = x
  while(abs(odrv0.axis0.controller.pos_setpoint - x) > 0.02): time.sleep(0.1)



