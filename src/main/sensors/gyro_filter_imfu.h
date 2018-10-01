static FAST_CODE void GYRO_FILTER_FUNCTION_NAME(gyroSensor_t *gyroSensor, timeDelta_t sampleDeltaUs)
{
    for (int axis = 0; axis < XYZ_AXIS_COUNT; axis++) {
#ifdef USE_GYRO_DATA_ANALYSE
        if (isDynamicFilterActive()) {
            gyroDataAnalysePush(&gyroSensor->gyroAnalyseState, axis, gyroSensor->gyroDev.gyroADCf[axis]);
            gyroSensor->gyroDev.gyroADCf[axis] = gyroSensor->notchFilterDynApplyFn((filter_t *)&gyroSensor->notchFilterDyn[axis], gyroSensor->gyroDev.gyroADCf[axis]);
            if (axis == X) {
                GYRO_FILTER_DEBUG_SET(DEBUG_FFT, 1, lrintf(gyroSensor->gyroDev.gyroADCf[axis])); // store data after dynamic notch
            }
        }
#endif
    }
}
