#ifndef ENUMS_H_
#define ENUMS_H_


enum FN_DATASET_TYPE
{
    FNDT_UNKNOWN,
    FNDT_NIFTI_SCALAR,
    FNDT_NIFTI_VECTOR,
    FNDT_NIFTI_DWI,
    FNDT_NIFTI2_SCALAR,
    FNDT_NIFTI2_VECTOR,
    FNDT_NIFTI2_DWI
};

enum FN_ALGO
{
    FNALGO_NONE,
    FNALGO_QBALL,
    FNALGO_TENSORFIT
};

#endif /* ENUMS_H_ */
