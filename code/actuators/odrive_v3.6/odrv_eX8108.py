
#odrv0.config.enable_brake_resistor = True
#odrv0.config.brake_resistance = 2
#odrv0.config.dc_max_positive_current = 18


odrv0.axis1.requested_state = AXIS_STATE_IDLE
odrv0.axis1.encoder.config.pre_calibrated = False
odrv0.axis1.motor.config.pre_calibrated = False
odrv0.axis1.config.startup_encoder_index_search = False

odrv0.axis1.controller.config.vel_limit = 20
odrv0.axis1.motor.config.pole_pairs = 21
odrv0.axis1.motor.config.torque_constant = 8.27 / 105
odrv0.axis1.motor.config.current_lim = 24 # max continuous current
odrv0.axis1.motor.config.calibration_current = 12
odrv0.axis1.config.calibration_lockin.current = 12
odrv0.axis1.encoder.config.cpr = 8192

odrv0.save_configuration()

odrv0.axis1.requested_state = AXIS_STATE_FULL_CALIBRATION_SEQUENCE

odrv0.axis1.encoder.config.use_index = True
odrv0.axis1.requested_state = AXIS_STATE_ENCODER_INDEX_SEARCH

odrv0.axis1.requested_state = AXIS_STATE_ENCODER_OFFSET_CALIBRATION

odrv0.axis1.encoder.config.pre_calibrated = True
odrv0.axis1.motor.config.pre_calibrated = True
odrv0.axis1.config.startup_encoder_index_search = True
odrv0.save_configuration()


# tuning, was done with 50V

odrv0.axis1.controller.config.vel_integrator_gain = 0
odrv0.axis1.controller.config.vel_gain = 0.25  # default 0.16666666
odrv0.axis1.controller.config.pos_gain = 150  # default 20
odrv0.axis1.controller.config.vel_integrator_gain = 0.5 * 10 * odrv0.axis1.controller.config.vel_gain
odrv0.axis1.requested_state = AXIS_STATE_IDLE
odrv0.save_configuration()



# filtered position control
odrv0.axis1.controller.config.input_filter_bandwidth = 2
odrv0.axis1.controller.config.input_mode = INPUT_MODE_POS_FILTER
odrv0.axis1.requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL



odrv0.axis1.requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL
odrv0.axis1.controller.input_pos = 1.5



