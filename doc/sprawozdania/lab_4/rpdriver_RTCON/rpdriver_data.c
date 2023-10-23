/*
 * rpdriver_data.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "rpdriver".
 *
 * Model version              : 1.314
 * Simulink Coder version : 9.0 (R2018b) 24-May-2018
 * C source code generated on : Mon Oct 23 10:35:49 2023
 *
 * Target selection: rtcon_rpend_usb2.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "rpdriver.h"
#include "rpdriver_private.h"

/* Block parameters (default storage) */
P_rpdriver_T rpdriver_P = {
  /* Expression: 1
   * Referenced by: '<Root>/Gain1'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<Root>/Normal'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<Root>/Reset'
   */
  1.0,

  /* Computed Parameter: SFunction_P1_Size
   * Referenced by: '<S1>/S-Function'
   */
  { 1.0, 1.0 },

  /* Expression: 1
   * Referenced by: '<S1>/S-Function'
   */
  1.0,

  /* Computed Parameter: SFunction_P2_Size
   * Referenced by: '<S1>/S-Function'
   */
  { 1.0, 1.0 },

  /* Expression: 0.01
   * Referenced by: '<S1>/S-Function'
   */
  0.01,

  /* Expression: 2*pi/20000
   * Referenced by: '<S1>/Pendulum Convert to rad'
   */
  0.00031415926535897931,

  /* Expression: pi
   * Referenced by: '<S3>/Constant'
   */
  3.1415926535897931,

  /* Expression: 0
   * Referenced by: '<S1>/Memory2'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S1>/rad2rad//s'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S1>/Memory'
   */
  0.0,

  /* Expression: 1/20000000
   * Referenced by: '<S1>/Gain1'
   */
  5.0E-8,

  /* Expression: 2*pi/4096
   * Referenced by: '<S1>/DC Convert to rad'
   */
  0.0015339807878856412,

  /* Expression: 0
   * Referenced by: '<S1>/Memory1'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S1>/rad2RPM'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S1>/DC Convert to [A]1'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<Root>/DC_Ctrl1'
   */
  0.0,

  /* Expression: sps.tv
   * Referenced by: '<S4>/Look-Up Table'
   */
  { 0.0, 5.0, 5.0, 10.0, 10.0, 15.0, 15.0, 20.0, 20.0, 25.0, 25.0, 30.0, 30.0,
    35.0, 35.0, 40.0, 40.0, 45.0, 45.0, 50.0, 50.0, 55.0, 55.0, 60.0, 60.0, 65.0,
    65.0, 70.0, 70.0, 75.0, 75.0, 80.0, 80.0, 85.0, 85.0, 90.0, 90.0, 95.0, 95.0,
    100.0, 100.0, 101.0 },

  /* Expression: sps.opv
   * Referenced by: '<S4>/Look-Up Table'
   */
  { -1.0, -1.0, -0.9, -0.9, -0.8, -0.8, -0.7, -0.7, -0.6, -0.6, -0.5, -0.5,
    -0.39999999999999991, -0.39999999999999991, -0.29999999999999993,
    -0.29999999999999993, -0.19999999999999996, -0.19999999999999996,
    -0.099999999999999978, -0.099999999999999978, 0.0, 0.0, 0.099999999999999978,
    0.099999999999999978, 0.19999999999999996, 0.19999999999999996,
    0.29999999999999993, 0.29999999999999993, 0.39999999999999991,
    0.39999999999999991, 0.5, 0.5, 0.6, 0.6, 0.7, 0.7, 0.8, 0.8, 0.9, 0.9, 1.0,
    1.0 },

  /* Expression: 0.6
   * Referenced by: '<Root>/DC_Ctrl2'
   */
  0.6,

  /* Expression: 1
   * Referenced by: '<Root>/Gain3'
   */
  1.0,

  /* Expression: [1;1]
   * Referenced by: '<S1>/Gain'
   */
  { 1.0, 1.0 },

  /* Expression: 1
   * Referenced by: '<S1>/Gain2'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S1>/Prescaler'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S1>/Saturation'
   */
  1.0,

  /* Expression: -1
   * Referenced by: '<S1>/Saturation'
   */
  -1.0,

  /* Expression: 0
   * Referenced by: '<S1>/ThermFlag'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S4>/Hit  Crossing'
   */
  0.0,

  /* Computed Parameter: ResetEncoders2_CurrentSetting
   * Referenced by: '<Root>/Reset Encoders2'
   */
  1U,

  /* Computed Parameter: ResetEncoders1_CurrentSetting
   * Referenced by: '<Root>/Reset Encoders1'
   */
  1U,

  /* Computed Parameter: ResetEncoders_CurrentSetting
   * Referenced by: '<Root>/Reset Encoders'
   */
  0U
};
