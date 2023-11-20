/*
 * rpdriver.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "rpdriver".
 *
 * Model version              : 1.343
 * Simulink Coder version : 9.0 (R2018b) 24-May-2018
 * C source code generated on : Mon Nov 20 08:59:21 2023
 *
 * Target selection: rtcon_rpend_usb2.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "rpdriver.h"
#include "rpdriver_private.h"
#include "rpdriver_dt.h"

/* Block signals (default storage) */
B_rpdriver_T rpdriver_B;

/* Block states (default storage) */
DW_rpdriver_T rpdriver_DW;

/* Real-time model */
RT_MODEL_rpdriver_T rpdriver_M_;
RT_MODEL_rpdriver_T *const rpdriver_M = &rpdriver_M_;
real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  int32_T u0_0;
  int32_T u1_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      u0_0 = 1;
    } else {
      u0_0 = -1;
    }

    if (u1 > 0.0) {
      u1_0 = 1;
    } else {
      u1_0 = -1;
    }

    y = atan2(u0_0, u1_0);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

/* Model step function */
void rpdriver_step(void)
{
  real_T rtb_Gain2;
  real_T Gain_tmp;
  real_T Gain_tmp_0;
  real_T Gain_tmp_1;

  /* S-Function (rtdacusb2_rpend_dd): '<S1>/S-Function' */

  /* Level2 S-Function Block: '<S1>/S-Function' (rtdacusb2_rpend_dd) */
  {
    SimStruct *rts = rpdriver_M->childSfunctions[0];
    sfcnOutputs(rts,1);
  }

  /* Gain: '<S1>/Pendulum Convert to rad' */
  rpdriver_B.PendulumAnglerad = rpdriver_P.PendulumConverttorad_Gain *
    rpdriver_B.SFunction_o2;

  /* Trigonometry: '<S3>/Trigonometric Function' incorporates:
   *  Trigonometry: '<S3>/Trigonometric Function1'
   *  Trigonometry: '<S3>/Trigonometric Function2'
   */
  rpdriver_B.PendPos_ZeroDown = rt_atan2d_snf(sin(rpdriver_B.PendulumAnglerad),
    cos(rpdriver_B.PendulumAnglerad));

  /* Sum: '<S3>/Add' incorporates:
   *  Constant: '<S3>/Constant'
   */
  rtb_Gain2 = rpdriver_B.PendulumAnglerad + rpdriver_P.Constant_Value;

  /* Trigonometry: '<S3>/Trigonometric Function3' incorporates:
   *  Trigonometry: '<S3>/Trigonometric Function4'
   *  Trigonometry: '<S3>/Trigonometric Function5'
   */
  rpdriver_B.PendPos_ZeroUp = rt_atan2d_snf(sin(rtb_Gain2), cos(rtb_Gain2));

  /* Gain: '<S1>/Gain1' incorporates:
   *  Memory: '<S1>/Memory'
   *  Sum: '<S1>/Add'
   */
  rpdriver_B.Periodms = (rpdriver_B.SFunction_o6 -
    rpdriver_DW.Memory_PreviousInput) * rpdriver_P.Gain1_Gain_h;

  /* Product: '<S1>/Divide1' incorporates:
   *  Gain: '<S1>/rad2rad//s'
   *  Memory: '<S1>/Memory2'
   *  Sum: '<S1>/Add2'
   */
  rpdriver_B.PendulumVelrads = (rpdriver_B.PendulumAnglerad -
    rpdriver_DW.Memory2_PreviousInput) * rpdriver_P.rad2rads_Gain /
    rpdriver_B.Periodms;

  /* Gain: '<S1>/DC Convert to rad' */
  rpdriver_B.DCAnglerad = rpdriver_P.DCConverttorad_Gain *
    rpdriver_B.SFunction_o3;

  /* Product: '<S1>/Divide' incorporates:
   *  Gain: '<S1>/rad2RPM'
   *  Memory: '<S1>/Memory1'
   *  Sum: '<S1>/Add1'
   */
  rpdriver_B.DCVelrads = (rpdriver_B.DCAnglerad -
    rpdriver_DW.Memory1_PreviousInput) * rpdriver_P.rad2RPM_Gain /
    rpdriver_B.Periodms;

  /* Gain: '<S1>/DC Convert to [A]1' */
  rpdriver_B.DCConverttoA1 = rpdriver_P.DCConverttoA1_Gain *
    rpdriver_B.SFunction_o4;

  /* Gain: '<Root>/Gain' incorporates:
   *  Constant: '<Root>/x_ep'
   *  Gain: '<Root>/Gain2'
   *  Gain: '<Root>/Gain4'
   *  Gain: '<Root>/Gain5'
   *  Sum: '<Root>/Sum1'
   */
  Gain_tmp = rpdriver_P.K[0] * (rpdriver_B.PendulumAnglerad -
    rpdriver_P.x_ep_Value[0]);
  Gain_tmp_0 = rpdriver_P.K[1] * (rpdriver_B.PendulumVelrads -
    rpdriver_P.x_ep_Value[1]);
  Gain_tmp_1 = rpdriver_P.K[2] * (rpdriver_B.DCVelrads - rpdriver_P.x_ep_Value[2]);
  rpdriver_B.Gain = (Gain_tmp + Gain_tmp_0) + Gain_tmp_1;

  /* Sum: '<Root>/Sum' incorporates:
   *  Constant: '<Root>/Constant1'
   */
  rpdriver_B.Sum = rpdriver_P.Constant1_Value - rpdriver_B.Gain;

  /* ManualSwitch: '<Root>/Reset Encoders1' incorporates:
   *  Constant: '<Root>/DC_Ctrl2'
   */
  if (rpdriver_P.ResetEncoders1_CurrentSetting == 1) {
    /* ManualSwitch: '<Root>/Reset Encoders2' incorporates:
     *  Constant: '<Root>/DC_Ctrl1'
     *  Gain: '<Root>/Gain1'
     *  Saturate: '<Root>/Saturation'
     */
    if (rpdriver_P.ResetEncoders2_CurrentSetting == 1) {
      rtb_Gain2 = rpdriver_P.DC_Ctrl1_Value;
    } else {
      if (rpdriver_B.Sum > rpdriver_P.Saturation_UpperSat) {
        /* Saturate: '<Root>/Saturation' */
        rtb_Gain2 = rpdriver_P.Saturation_UpperSat;
      } else if (rpdriver_B.Sum < rpdriver_P.Saturation_LowerSat) {
        /* Saturate: '<Root>/Saturation' */
        rtb_Gain2 = rpdriver_P.Saturation_LowerSat;
      } else {
        /* Saturate: '<Root>/Saturation' */
        rtb_Gain2 = rpdriver_B.Sum;
      }

      rtb_Gain2 *= rpdriver_P.Gain1_Gain;
    }

    /* End of ManualSwitch: '<Root>/Reset Encoders2' */
  } else {
    rtb_Gain2 = rpdriver_P.DC_Ctrl2_Value;
  }

  /* End of ManualSwitch: '<Root>/Reset Encoders1' */

  /* Gain: '<Root>/Gain3' */
  rpdriver_B.Control = rpdriver_P.Gain3_Gain * rtb_Gain2;

  /* Scope: '<Root>/PlotState' */
  {
    StructLogVar *svar = (StructLogVar *)rpdriver_DW.PlotState_PWORK.LoggedData
      [0];
    LogVar *var = svar->signals.values;

    /* time */
    {
      double locTime = rpdriver_M->Timing.t[1];
      ;
      rt_UpdateLogVar((LogVar *)svar->time, &locTime, 0);
    }

    /* signals */
    {
      real_T up0[1];
      up0[0] = rpdriver_B.PendulumAnglerad;
      rt_UpdateLogVar((LogVar *)var, up0, 0);
      var = var->next;
    }

    {
      real_T up1[1];
      up1[0] = rpdriver_B.PendPos_ZeroDown;
      rt_UpdateLogVar((LogVar *)var, up1, 0);
      var = var->next;
    }

    {
      real_T up2[1];
      up2[0] = rpdriver_B.PendPos_ZeroUp;
      rt_UpdateLogVar((LogVar *)var, up2, 0);
      var = var->next;
    }

    {
      real_T up3[1];
      up3[0] = rpdriver_B.PendulumVelrads;
      rt_UpdateLogVar((LogVar *)var, up3, 0);
      var = var->next;
    }

    {
      real_T up4[1];
      up4[0] = rpdriver_B.DCAnglerad;
      rt_UpdateLogVar((LogVar *)var, up4, 0);
      var = var->next;
    }

    {
      real_T up5[1];
      up5[0] = rpdriver_B.DCVelrads;
      rt_UpdateLogVar((LogVar *)var, up5, 0);
      var = var->next;
    }

    {
      real_T up6[1];
      up6[0] = rpdriver_B.DCConverttoA1;
      rt_UpdateLogVar((LogVar *)var, up6, 0);
      var = var->next;
    }

    {
      real_T up7[1];
      up7[0] = rpdriver_B.Control;
      rt_UpdateLogVar((LogVar *)var, up7, 0);
    }
  }

  /* Gain: '<Root>/Gain2' */
  rpdriver_B.Gain2 = Gain_tmp;

  /* Gain: '<Root>/Gain4' */
  rpdriver_B.Gain4 = Gain_tmp_0;

  /* Gain: '<Root>/Gain5' */
  rpdriver_B.Gain5 = Gain_tmp_1;

  /* Scope: '<Root>/Scope' */
  {
    StructLogVar *svar = (StructLogVar *)rpdriver_DW.Scope_PWORK.LoggedData[0];
    LogVar *var = svar->signals.values;

    /* time */
    {
      double locTime = rpdriver_M->Timing.t[1];
      ;
      rt_UpdateLogVar((LogVar *)svar->time, &locTime, 0);
    }

    /* signals */
    {
      real_T up0[1];
      up0[0] = rpdriver_B.Gain;
      rt_UpdateLogVar((LogVar *)var, up0, 0);
      var = var->next;
    }

    {
      real_T up1[1];
      up1[0] = rpdriver_B.Gain2;
      rt_UpdateLogVar((LogVar *)var, up1, 0);
      var = var->next;
    }

    {
      real_T up2[1];
      up2[0] = rpdriver_B.Gain4;
      rt_UpdateLogVar((LogVar *)var, up2, 0);
      var = var->next;
    }

    {
      real_T up3[1];
      up3[0] = rpdriver_B.Gain5;
      rt_UpdateLogVar((LogVar *)var, up3, 0);
    }
  }

  /* ManualSwitch: '<Root>/Reset Encoders' incorporates:
   *  Constant: '<Root>/Normal'
   *  Constant: '<Root>/Reset'
   */
  if (rpdriver_P.ResetEncoders_CurrentSetting == 1) {
    rtb_Gain2 = rpdriver_P.Reset_Value;
  } else {
    rtb_Gain2 = rpdriver_P.Normal_Value;
  }

  /* End of ManualSwitch: '<Root>/Reset Encoders' */

  /* Gain: '<S1>/Gain' */
  rpdriver_B.Gain_j[0] = rpdriver_P.Gain_Gain[0] * rtb_Gain2;
  rpdriver_B.Gain_j[1] = rpdriver_P.Gain_Gain[1] * rtb_Gain2;

  /* Constant: '<S1>/Prescaler' */
  rpdriver_B.Prescaler = rpdriver_P.Prescaler_Value;

  /* Gain: '<S1>/Gain2' */
  Gain_tmp = rpdriver_P.Gain2_Gain * rpdriver_B.Control;

  /* Saturate: '<S1>/Saturation' */
  if (Gain_tmp > rpdriver_P.Saturation_UpperSat_h) {
    rpdriver_B.Saturation = rpdriver_P.Saturation_UpperSat_h;
  } else if (Gain_tmp < rpdriver_P.Saturation_LowerSat_f) {
    rpdriver_B.Saturation = rpdriver_P.Saturation_LowerSat_f;
  } else {
    rpdriver_B.Saturation = Gain_tmp;
  }

  /* End of Saturate: '<S1>/Saturation' */

  /* Constant: '<S1>/ThermFlag' */
  rpdriver_B.ThermFlag = rpdriver_P.ThermFlag_Value;

  /* Matfile logging */
  rt_UpdateTXYLogVars(rpdriver_M->rtwLogInfo, (rpdriver_M->Timing.t));

  /* Update for Memory: '<S1>/Memory2' */
  rpdriver_DW.Memory2_PreviousInput = rpdriver_B.PendulumAnglerad;

  /* Update for Memory: '<S1>/Memory' */
  rpdriver_DW.Memory_PreviousInput = rpdriver_B.SFunction_o6;

  /* Update for Memory: '<S1>/Memory1' */
  rpdriver_DW.Memory1_PreviousInput = rpdriver_B.DCAnglerad;

  /* External mode */
  rtExtModeUploadCheckTrigger(2);

  {                                    /* Sample time: [0.0s, 0.0s] */
    rtExtModeUpload(0, (real_T)rpdriver_M->Timing.t[0]);
  }

  {                                    /* Sample time: [0.01s, 0.0s] */
    rtExtModeUpload(1, (real_T)rpdriver_M->Timing.t[1]);
  }

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.0s, 0.0s] */
    if ((rtmGetTFinal(rpdriver_M)!=-1) &&
        !((rtmGetTFinal(rpdriver_M)-rpdriver_M->Timing.t[0]) >
          rpdriver_M->Timing.t[0] * (DBL_EPSILON))) {
      rtmSetErrorStatus(rpdriver_M, "Simulation finished");
    }

    if (rtmGetStopRequested(rpdriver_M)) {
      rtmSetErrorStatus(rpdriver_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++rpdriver_M->Timing.clockTick0)) {
    ++rpdriver_M->Timing.clockTickH0;
  }

  rpdriver_M->Timing.t[0] = rpdriver_M->Timing.clockTick0 *
    rpdriver_M->Timing.stepSize0 + rpdriver_M->Timing.clockTickH0 *
    rpdriver_M->Timing.stepSize0 * 4294967296.0;

  {
    /* Update absolute timer for sample time: [0.01s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++rpdriver_M->Timing.clockTick1)) {
      ++rpdriver_M->Timing.clockTickH1;
    }

    rpdriver_M->Timing.t[1] = rpdriver_M->Timing.clockTick1 *
      rpdriver_M->Timing.stepSize1 + rpdriver_M->Timing.clockTickH1 *
      rpdriver_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Model initialize function */
void rpdriver_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)rpdriver_M, 0,
                sizeof(RT_MODEL_rpdriver_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&rpdriver_M->solverInfo,
                          &rpdriver_M->Timing.simTimeStep);
    rtsiSetTPtr(&rpdriver_M->solverInfo, &rtmGetTPtr(rpdriver_M));
    rtsiSetStepSizePtr(&rpdriver_M->solverInfo, &rpdriver_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&rpdriver_M->solverInfo, (&rtmGetErrorStatus
      (rpdriver_M)));
    rtsiSetRTModelPtr(&rpdriver_M->solverInfo, rpdriver_M);
  }

  rtsiSetSimTimeStep(&rpdriver_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&rpdriver_M->solverInfo,"FixedStepDiscrete");
  rpdriver_M->solverInfoPtr = (&rpdriver_M->solverInfo);

  /* Initialize timing info */
  {
    int_T *mdlTsMap = rpdriver_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    rpdriver_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    rpdriver_M->Timing.sampleTimes = (&rpdriver_M->Timing.sampleTimesArray[0]);
    rpdriver_M->Timing.offsetTimes = (&rpdriver_M->Timing.offsetTimesArray[0]);

    /* task periods */
    rpdriver_M->Timing.sampleTimes[0] = (0.0);
    rpdriver_M->Timing.sampleTimes[1] = (0.01);

    /* task offsets */
    rpdriver_M->Timing.offsetTimes[0] = (0.0);
    rpdriver_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(rpdriver_M, &rpdriver_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = rpdriver_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    rpdriver_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(rpdriver_M, 999.0);
  rpdriver_M->Timing.stepSize0 = 0.01;
  rpdriver_M->Timing.stepSize1 = 0.01;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = NULL;
    rpdriver_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(rpdriver_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(rpdriver_M->rtwLogInfo, (NULL));
    rtliSetLogT(rpdriver_M->rtwLogInfo, "tout");
    rtliSetLogX(rpdriver_M->rtwLogInfo, "");
    rtliSetLogXFinal(rpdriver_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(rpdriver_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(rpdriver_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(rpdriver_M->rtwLogInfo, 0);
    rtliSetLogDecimation(rpdriver_M->rtwLogInfo, 1);
    rtliSetLogY(rpdriver_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(rpdriver_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(rpdriver_M->rtwLogInfo, (NULL));
  }

  /* External mode info */
  rpdriver_M->Sizes.checksums[0] = (2582009929U);
  rpdriver_M->Sizes.checksums[1] = (3579302495U);
  rpdriver_M->Sizes.checksums[2] = (623256540U);
  rpdriver_M->Sizes.checksums[3] = (3991157604U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[7];
    rpdriver_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = &rtAlwaysEnabled;
    systemRan[6] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(rpdriver_M->extModeInfo,
      &rpdriver_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(rpdriver_M->extModeInfo, rpdriver_M->Sizes.checksums);
    rteiSetTPtr(rpdriver_M->extModeInfo, rtmGetTPtr(rpdriver_M));
  }

  rpdriver_M->solverInfoPtr = (&rpdriver_M->solverInfo);
  rpdriver_M->Timing.stepSize = (0.01);
  rtsiSetFixedStepSize(&rpdriver_M->solverInfo, 0.01);
  rtsiSetSolverMode(&rpdriver_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  (void) memset(((void *) &rpdriver_B), 0,
                sizeof(B_rpdriver_T));

  /* states (dwork) */
  (void) memset((void *)&rpdriver_DW, 0,
                sizeof(DW_rpdriver_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    rpdriver_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 14;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* child S-Function registration */
  {
    RTWSfcnInfo *sfcnInfo = &rpdriver_M->NonInlinedSFcns.sfcnInfo;
    rpdriver_M->sfcnInfo = (sfcnInfo);
    rtssSetErrorStatusPtr(sfcnInfo, (&rtmGetErrorStatus(rpdriver_M)));
    rtssSetNumRootSampTimesPtr(sfcnInfo, &rpdriver_M->Sizes.numSampTimes);
    rpdriver_M->NonInlinedSFcns.taskTimePtrs[0] = &(rtmGetTPtr(rpdriver_M)[0]);
    rpdriver_M->NonInlinedSFcns.taskTimePtrs[1] = &(rtmGetTPtr(rpdriver_M)[1]);
    rtssSetTPtrPtr(sfcnInfo,rpdriver_M->NonInlinedSFcns.taskTimePtrs);
    rtssSetTStartPtr(sfcnInfo, &rtmGetTStart(rpdriver_M));
    rtssSetTFinalPtr(sfcnInfo, &rtmGetTFinal(rpdriver_M));
    rtssSetTimeOfLastOutputPtr(sfcnInfo, &rtmGetTimeOfLastOutput(rpdriver_M));
    rtssSetStepSizePtr(sfcnInfo, &rpdriver_M->Timing.stepSize);
    rtssSetStopRequestedPtr(sfcnInfo, &rtmGetStopRequested(rpdriver_M));
    rtssSetDerivCacheNeedsResetPtr(sfcnInfo, &rpdriver_M->derivCacheNeedsReset);
    rtssSetZCCacheNeedsResetPtr(sfcnInfo, &rpdriver_M->zCCacheNeedsReset);
    rtssSetContTimeOutputInconsistentWithStateAtMajorStepPtr(sfcnInfo,
      &rpdriver_M->CTOutputIncnstWithState);
    rtssSetSampleHitsPtr(sfcnInfo, &rpdriver_M->Timing.sampleHits);
    rtssSetPerTaskSampleHitsPtr(sfcnInfo, &rpdriver_M->Timing.perTaskSampleHits);
    rtssSetSimModePtr(sfcnInfo, &rpdriver_M->simMode);
    rtssSetSolverInfoPtr(sfcnInfo, &rpdriver_M->solverInfoPtr);
  }

  rpdriver_M->Sizes.numSFcns = (1);

  /* register each child */
  {
    (void) memset((void *)&rpdriver_M->NonInlinedSFcns.childSFunctions[0], 0,
                  1*sizeof(SimStruct));
    rpdriver_M->childSfunctions =
      (&rpdriver_M->NonInlinedSFcns.childSFunctionPtrs[0]);
    rpdriver_M->childSfunctions[0] =
      (&rpdriver_M->NonInlinedSFcns.childSFunctions[0]);

    /* Level2 S-Function Block: rpdriver/<S1>/S-Function (rtdacusb2_rpend_dd) */
    {
      SimStruct *rts = rpdriver_M->childSfunctions[0];

      /* timing info */
      time_T *sfcnPeriod = rpdriver_M->NonInlinedSFcns.Sfcn0.sfcnPeriod;
      time_T *sfcnOffset = rpdriver_M->NonInlinedSFcns.Sfcn0.sfcnOffset;
      int_T *sfcnTsMap = rpdriver_M->NonInlinedSFcns.Sfcn0.sfcnTsMap;
      (void) memset((void*)sfcnPeriod, 0,
                    sizeof(time_T)*1);
      (void) memset((void*)sfcnOffset, 0,
                    sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      {
        ssSetBlkInfo2Ptr(rts, &rpdriver_M->NonInlinedSFcns.blkInfo2[0]);
      }

      _ssSetBlkInfo2PortInfo2Ptr(rts,
        &rpdriver_M->NonInlinedSFcns.inputOutputPortInfo2[0]);

      /* Set up the mdlInfo pointer */
      ssSetRTWSfcnInfo(rts, rpdriver_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts, &rpdriver_M->NonInlinedSFcns.methods2[0]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts, &rpdriver_M->NonInlinedSFcns.methods3[0]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts, &rpdriver_M->NonInlinedSFcns.methods4[0]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts, &rpdriver_M->NonInlinedSFcns.statesInfo2[0]);
        ssSetPeriodicStatesInfo(rts,
          &rpdriver_M->NonInlinedSFcns.periodicStatesInfo[0]);
      }

      /* inputs */
      {
        _ssSetNumInputPorts(rts, 4);
        ssSetPortInfoForInputs(rts,
          &rpdriver_M->NonInlinedSFcns.Sfcn0.inputPortInfo[0]);
        _ssSetPortInfo2ForInputUnits(rts,
          &rpdriver_M->NonInlinedSFcns.Sfcn0.inputPortUnits[0]);
        ssSetInputPortUnit(rts, 0, 0);
        ssSetInputPortUnit(rts, 1, 0);
        ssSetInputPortUnit(rts, 2, 0);
        ssSetInputPortUnit(rts, 3, 0);
        _ssSetPortInfo2ForInputCoSimAttribute(rts,
          &rpdriver_M->NonInlinedSFcns.Sfcn0.inputPortCoSimAttribute[0]);
        ssSetInputPortIsContinuousQuantity(rts, 0, 0);
        ssSetInputPortIsContinuousQuantity(rts, 1, 0);
        ssSetInputPortIsContinuousQuantity(rts, 2, 0);
        ssSetInputPortIsContinuousQuantity(rts, 3, 0);

        /* port 0 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &rpdriver_M->NonInlinedSFcns.Sfcn0.UPtrs0;
          sfcnUPtrs[0] = &rpdriver_B.Saturation;
          ssSetInputPortSignalPtrs(rts, 0, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 0, 1);
          ssSetInputPortWidth(rts, 0, 1);
        }

        /* port 1 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &rpdriver_M->NonInlinedSFcns.Sfcn0.UPtrs1;
          sfcnUPtrs[0] = rpdriver_B.Gain_j;
          sfcnUPtrs[1] = &rpdriver_B.Gain_j[1];
          ssSetInputPortSignalPtrs(rts, 1, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 1, 1);
          ssSetInputPortWidth(rts, 1, 2);
        }

        /* port 2 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &rpdriver_M->NonInlinedSFcns.Sfcn0.UPtrs2;
          sfcnUPtrs[0] = &rpdriver_B.Prescaler;
          ssSetInputPortSignalPtrs(rts, 2, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 2, 1);
          ssSetInputPortWidth(rts, 2, 1);
        }

        /* port 3 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &rpdriver_M->NonInlinedSFcns.Sfcn0.UPtrs3;
          sfcnUPtrs[0] = &rpdriver_B.ThermFlag;
          ssSetInputPortSignalPtrs(rts, 3, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 3, 1);
          ssSetInputPortWidth(rts, 3, 1);
        }
      }

      /* outputs */
      {
        ssSetPortInfoForOutputs(rts,
          &rpdriver_M->NonInlinedSFcns.Sfcn0.outputPortInfo[0]);
        _ssSetNumOutputPorts(rts, 7);
        _ssSetPortInfo2ForOutputUnits(rts,
          &rpdriver_M->NonInlinedSFcns.Sfcn0.outputPortUnits[0]);
        ssSetOutputPortUnit(rts, 0, 0);
        ssSetOutputPortUnit(rts, 1, 0);
        ssSetOutputPortUnit(rts, 2, 0);
        ssSetOutputPortUnit(rts, 3, 0);
        ssSetOutputPortUnit(rts, 4, 0);
        ssSetOutputPortUnit(rts, 5, 0);
        ssSetOutputPortUnit(rts, 6, 0);
        _ssSetPortInfo2ForOutputCoSimAttribute(rts,
          &rpdriver_M->NonInlinedSFcns.Sfcn0.outputPortCoSimAttribute[0]);
        ssSetOutputPortIsContinuousQuantity(rts, 0, 0);
        ssSetOutputPortIsContinuousQuantity(rts, 1, 0);
        ssSetOutputPortIsContinuousQuantity(rts, 2, 0);
        ssSetOutputPortIsContinuousQuantity(rts, 3, 0);
        ssSetOutputPortIsContinuousQuantity(rts, 4, 0);
        ssSetOutputPortIsContinuousQuantity(rts, 5, 0);
        ssSetOutputPortIsContinuousQuantity(rts, 6, 0);

        /* port 0 */
        {
          _ssSetOutputPortNumDimensions(rts, 0, 1);
          ssSetOutputPortWidth(rts, 0, 1);
          ssSetOutputPortSignal(rts, 0, ((real_T *) &rpdriver_B.SFunction_o1));
        }

        /* port 1 */
        {
          _ssSetOutputPortNumDimensions(rts, 1, 1);
          ssSetOutputPortWidth(rts, 1, 1);
          ssSetOutputPortSignal(rts, 1, ((real_T *) &rpdriver_B.SFunction_o2));
        }

        /* port 2 */
        {
          _ssSetOutputPortNumDimensions(rts, 2, 1);
          ssSetOutputPortWidth(rts, 2, 1);
          ssSetOutputPortSignal(rts, 2, ((real_T *) &rpdriver_B.SFunction_o3));
        }

        /* port 3 */
        {
          _ssSetOutputPortNumDimensions(rts, 3, 1);
          ssSetOutputPortWidth(rts, 3, 1);
          ssSetOutputPortSignal(rts, 3, ((real_T *) &rpdriver_B.SFunction_o4));
        }

        /* port 4 */
        {
          _ssSetOutputPortNumDimensions(rts, 4, 1);
          ssSetOutputPortWidth(rts, 4, 1);
          ssSetOutputPortSignal(rts, 4, ((real_T *) &rpdriver_B.SFunction_o5));
        }

        /* port 5 */
        {
          _ssSetOutputPortNumDimensions(rts, 5, 1);
          ssSetOutputPortWidth(rts, 5, 1);
          ssSetOutputPortSignal(rts, 5, ((real_T *) &rpdriver_B.SFunction_o6));
        }

        /* port 6 */
        {
          _ssSetOutputPortNumDimensions(rts, 6, 1);
          ssSetOutputPortWidth(rts, 6, 2);
          ssSetOutputPortSignal(rts, 6, ((real_T *) rpdriver_B.SFunction_o7));
        }
      }

      /* path info */
      ssSetModelName(rts, "S-Function");
      ssSetPath(rts, "rpdriver/RP Driver/S-Function");
      ssSetRTModel(rts,rpdriver_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &rpdriver_M->NonInlinedSFcns.Sfcn0.params;
        ssSetSFcnParamsCount(rts, 2);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)rpdriver_P.SFunction_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)rpdriver_P.SFunction_P2_Size);
      }

      /* registration */
      rtdacusb2_rpend_dd(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.01);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 1;

      /* set compiled values of dynamic vector attributes */
      ssSetNumNonsampledZCs(rts, 0);

      /* Update connectivity flags for each port */
      _ssSetInputPortConnected(rts, 0, 1);
      _ssSetInputPortConnected(rts, 1, 1);
      _ssSetInputPortConnected(rts, 2, 1);
      _ssSetInputPortConnected(rts, 3, 1);
      _ssSetOutputPortConnected(rts, 0, 1);
      _ssSetOutputPortConnected(rts, 1, 1);
      _ssSetOutputPortConnected(rts, 2, 1);
      _ssSetOutputPortConnected(rts, 3, 1);
      _ssSetOutputPortConnected(rts, 4, 1);
      _ssSetOutputPortConnected(rts, 5, 1);
      _ssSetOutputPortConnected(rts, 6, 1);
      _ssSetOutputPortBeingMerged(rts, 0, 0);
      _ssSetOutputPortBeingMerged(rts, 1, 0);
      _ssSetOutputPortBeingMerged(rts, 2, 0);
      _ssSetOutputPortBeingMerged(rts, 3, 0);
      _ssSetOutputPortBeingMerged(rts, 4, 0);
      _ssSetOutputPortBeingMerged(rts, 5, 0);
      _ssSetOutputPortBeingMerged(rts, 6, 0);

      /* Update the BufferDstPort flags for each input port */
      ssSetInputPortBufferDstPort(rts, 0, -1);
      ssSetInputPortBufferDstPort(rts, 1, -1);
      ssSetInputPortBufferDstPort(rts, 2, -1);
      ssSetInputPortBufferDstPort(rts, 3, -1);
    }
  }

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(rpdriver_M->rtwLogInfo, 0.0, rtmGetTFinal
    (rpdriver_M), rpdriver_M->Timing.stepSize0, (&rtmGetErrorStatus(rpdriver_M)));

  /* Start for S-Function (rtdacusb2_rpend_dd): '<S1>/S-Function' */
  /* Level2 S-Function Block: '<S1>/S-Function' (rtdacusb2_rpend_dd) */
  {
    SimStruct *rts = rpdriver_M->childSfunctions[0];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* Start for Scope: '<Root>/PlotState' */
  {
    RTWLogSignalInfo rt_ScopeSignalInfo;
    static int_T rt_ScopeSignalWidths[] = { 1, 1, 1, 1, 1, 1, 1, 1 };

    static int_T rt_ScopeSignalNumDimensions[] = { 1, 1, 1, 1, 1, 1, 1, 1 };

    static int_T rt_ScopeSignalDimensions[] = { 1, 1, 1, 1, 1, 1, 1, 1 };

    static void *rt_ScopeCurrSigDims[] = { (NULL), (NULL), (NULL), (NULL), (NULL),
      (NULL), (NULL), (NULL) };

    static int_T rt_ScopeCurrSigDimsSize[] = { 4, 4, 4, 4, 4, 4, 4, 4 };

    static const char_T *rt_ScopeSignalLabels[] = { "<Pendulum Angle [rad]>",
      "<PendPos_ZeroDown>",
      "<PendPos_ZeroUp>",
      "<Pendulum Vel [rad/s]>",
      "<DC Angle [rad]>",
      "<DC Vel [rad/s]>",
      "DC Current",
      "Control" };

    static char_T rt_ScopeSignalTitles[] =
      "<Pendulum Angle [rad]><PendPos_ZeroDown><PendPos_ZeroUp><Pendulum Vel [rad/s]><DC Angle [rad]><DC Vel [rad/s]>DC CurrentControl";
    static int_T rt_ScopeSignalTitleLengths[] = { 22, 18, 16, 22, 16, 16, 10, 7
    };

    static boolean_T rt_ScopeSignalIsVarDims[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

    static int_T rt_ScopeSignalPlotStyles[] = { 1, 1, 1, 1, 1, 1, 1, 1 };

    BuiltInDTypeId dTypes[8] = { SS_DOUBLE, SS_DOUBLE, SS_DOUBLE, SS_DOUBLE,
      SS_DOUBLE, SS_DOUBLE, SS_DOUBLE, SS_DOUBLE };

    static char_T rt_ScopeBlockName[] = "rpdriver/PlotState";
    static int_T rt_ScopeFrameData[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

    static RTWPreprocessingFcnPtr rt_ScopeSignalLoggingPreprocessingFcnPtrs[] =
      {
      (NULL), (NULL), (NULL), (NULL), (NULL), (NULL), (NULL), (NULL)
    };

    rt_ScopeSignalInfo.numSignals = 8;
    rt_ScopeSignalInfo.numCols = rt_ScopeSignalWidths;
    rt_ScopeSignalInfo.numDims = rt_ScopeSignalNumDimensions;
    rt_ScopeSignalInfo.dims = rt_ScopeSignalDimensions;
    rt_ScopeSignalInfo.isVarDims = rt_ScopeSignalIsVarDims;
    rt_ScopeSignalInfo.currSigDims = rt_ScopeCurrSigDims;
    rt_ScopeSignalInfo.currSigDimsSize = rt_ScopeCurrSigDimsSize;
    rt_ScopeSignalInfo.dataTypes = dTypes;
    rt_ScopeSignalInfo.complexSignals = (NULL);
    rt_ScopeSignalInfo.frameData = rt_ScopeFrameData;
    rt_ScopeSignalInfo.preprocessingPtrs =
      rt_ScopeSignalLoggingPreprocessingFcnPtrs;
    rt_ScopeSignalInfo.labels.cptr = rt_ScopeSignalLabels;
    rt_ScopeSignalInfo.titles = rt_ScopeSignalTitles;
    rt_ScopeSignalInfo.titleLengths = rt_ScopeSignalTitleLengths;
    rt_ScopeSignalInfo.plotStyles = rt_ScopeSignalPlotStyles;
    rt_ScopeSignalInfo.blockNames.cptr = (NULL);
    rt_ScopeSignalInfo.stateNames.cptr = (NULL);
    rt_ScopeSignalInfo.crossMdlRef = (NULL);
    rt_ScopeSignalInfo.dataTypeConvert = (NULL);
    rpdriver_DW.PlotState_PWORK.LoggedData[0] = rt_CreateStructLogVar(
      rpdriver_M->rtwLogInfo,
      0.0,
      rtmGetTFinal(rpdriver_M),
      rpdriver_M->Timing.stepSize0,
      (&rtmGetErrorStatus(rpdriver_M)),
      "LQR_pomiary_stanu_6",
      1,
      0,
      1,
      0.01,
      &rt_ScopeSignalInfo,
      rt_ScopeBlockName);
    if (rpdriver_DW.PlotState_PWORK.LoggedData[0] == (NULL))
      return;
  }

  /* Start for Scope: '<Root>/Scope' */
  {
    RTWLogSignalInfo rt_ScopeSignalInfo;
    static int_T rt_ScopeSignalWidths[] = { 1, 1, 1, 1 };

    static int_T rt_ScopeSignalNumDimensions[] = { 1, 1, 1, 1 };

    static int_T rt_ScopeSignalDimensions[] = { 1, 1, 1, 1 };

    static void *rt_ScopeCurrSigDims[] = { (NULL), (NULL), (NULL), (NULL) };

    static int_T rt_ScopeCurrSigDimsSize[] = { 4, 4, 4, 4 };

    static const char_T *rt_ScopeSignalLabels[] = { "",
      "",
      "",
      "" };

    static char_T rt_ScopeSignalTitles[] = "";
    static int_T rt_ScopeSignalTitleLengths[] = { 0, 0, 0, 0 };

    static boolean_T rt_ScopeSignalIsVarDims[] = { 0, 0, 0, 0 };

    static int_T rt_ScopeSignalPlotStyles[] = { 1, 1, 1, 1 };

    BuiltInDTypeId dTypes[4] = { SS_DOUBLE, SS_DOUBLE, SS_DOUBLE, SS_DOUBLE };

    static char_T rt_ScopeBlockName[] = "rpdriver/Scope";
    static int_T rt_ScopeFrameData[] = { 0, 0, 0, 0 };

    static RTWPreprocessingFcnPtr rt_ScopeSignalLoggingPreprocessingFcnPtrs[] =
      {
      (NULL), (NULL), (NULL), (NULL)
    };

    rt_ScopeSignalInfo.numSignals = 4;
    rt_ScopeSignalInfo.numCols = rt_ScopeSignalWidths;
    rt_ScopeSignalInfo.numDims = rt_ScopeSignalNumDimensions;
    rt_ScopeSignalInfo.dims = rt_ScopeSignalDimensions;
    rt_ScopeSignalInfo.isVarDims = rt_ScopeSignalIsVarDims;
    rt_ScopeSignalInfo.currSigDims = rt_ScopeCurrSigDims;
    rt_ScopeSignalInfo.currSigDimsSize = rt_ScopeCurrSigDimsSize;
    rt_ScopeSignalInfo.dataTypes = dTypes;
    rt_ScopeSignalInfo.complexSignals = (NULL);
    rt_ScopeSignalInfo.frameData = rt_ScopeFrameData;
    rt_ScopeSignalInfo.preprocessingPtrs =
      rt_ScopeSignalLoggingPreprocessingFcnPtrs;
    rt_ScopeSignalInfo.labels.cptr = rt_ScopeSignalLabels;
    rt_ScopeSignalInfo.titles = rt_ScopeSignalTitles;
    rt_ScopeSignalInfo.titleLengths = rt_ScopeSignalTitleLengths;
    rt_ScopeSignalInfo.plotStyles = rt_ScopeSignalPlotStyles;
    rt_ScopeSignalInfo.blockNames.cptr = (NULL);
    rt_ScopeSignalInfo.stateNames.cptr = (NULL);
    rt_ScopeSignalInfo.crossMdlRef = (NULL);
    rt_ScopeSignalInfo.dataTypeConvert = (NULL);
    rpdriver_DW.Scope_PWORK.LoggedData[0] = rt_CreateStructLogVar(
      rpdriver_M->rtwLogInfo,
      0.0,
      rtmGetTFinal(rpdriver_M),
      rpdriver_M->Timing.stepSize0,
      (&rtmGetErrorStatus(rpdriver_M)),
      "Sterowania_lqr_6",
      1,
      0,
      1,
      0.01,
      &rt_ScopeSignalInfo,
      rt_ScopeBlockName);
    if (rpdriver_DW.Scope_PWORK.LoggedData[0] == (NULL))
      return;
  }

  /* Start for Constant: '<S1>/Prescaler' */
  rpdriver_B.Prescaler = rpdriver_P.Prescaler_Value;

  /* Start for Constant: '<S1>/ThermFlag' */
  rpdriver_B.ThermFlag = rpdriver_P.ThermFlag_Value;

  /* InitializeConditions for Memory: '<S1>/Memory2' */
  rpdriver_DW.Memory2_PreviousInput = rpdriver_P.Memory2_InitialCondition;

  /* InitializeConditions for Memory: '<S1>/Memory' */
  rpdriver_DW.Memory_PreviousInput = rpdriver_P.Memory_InitialCondition;

  /* InitializeConditions for Memory: '<S1>/Memory1' */
  rpdriver_DW.Memory1_PreviousInput = rpdriver_P.Memory1_InitialCondition;
}

/* Model terminate function */
void rpdriver_terminate(void)
{
  /* Terminate for S-Function (rtdacusb2_rpend_dd): '<S1>/S-Function' */
  /* Level2 S-Function Block: '<S1>/S-Function' (rtdacusb2_rpend_dd) */
  {
    SimStruct *rts = rpdriver_M->childSfunctions[0];
    sfcnTerminate(rts);
  }
}

#include <stdio.h>

/* Final time from "Simulation Parameters"   */
real_T finaltime = 999.0;
real_T StepSize = 0.01;

////////////////////////////////////////////////
//
//  Return compilation date and time
//
char *GetDateAndTime( void )
{
  static char AuxStr[ 128 ];
  sprintf( AuxStr, "%s %s", __DATE__, __TIME__ );
  return( AuxStr );
}
