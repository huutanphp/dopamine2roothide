#ifndef PATCHFINDER_ARM64_H
#define PATCHFINDER_ARM64_H

#include "PatchFinder.h"

typedef enum {
    ARM64_XREF_TYPE_BL = 0,
    ARM64_XREF_TYPE_B,
    ARM64_XREF_TYPE_B_COND,
    ARM64_XREF_TYPE_BC_COND,
    ARM64_XREF_TYPE_CBZ,
    ARM64_XREF_TYPE_CBNZ,
    ARM64_XREF_TYPE_TBZ,
    ARM64_XREF_TYPE_TBNZ,
    ARM64_XREF_TYPE_ADR,
    ARM64_XREF_TYPE_ADRP_ADD,
    ARM64_XREF_TYPE_ADRP_LDR,
    ARM64_XREF_TYPE_ADRP_STR,
    ARM64_XREF_TYPE_POINTER,
} Arm64XrefType;

typedef enum {
    ARM64_XREF_TYPE_MASK_BL = (1 << ARM64_XREF_TYPE_BL),
    ARM64_XREF_TYPE_MASK_CALL = (ARM64_XREF_TYPE_MASK_BL),

    ARM64_XREF_TYPE_MASK_B  = (1 << ARM64_XREF_TYPE_B),
    ARM64_XREF_TYPE_MASK_B_COND = (1 << ARM64_XREF_TYPE_B_COND),
    ARM64_XREF_TYPE_MASK_BC_COND = (1 << ARM64_XREF_TYPE_BC_COND),
    ARM64_XREF_TYPE_MASK_CBZ = (1 << ARM64_XREF_TYPE_CBZ),
    ARM64_XREF_TYPE_MASK_CBNZ = (1 << ARM64_XREF_TYPE_CBNZ),
    ARM64_XREF_TYPE_MASK_TBZ = (1 << ARM64_XREF_TYPE_TBZ),
    ARM64_XREF_TYPE_MASK_TBNZ = (1 << ARM64_XREF_TYPE_TBNZ),
    ARM64_XREF_TYPE_MASK_JUMP = (ARM64_XREF_TYPE_B | ARM64_XREF_TYPE_MASK_B_COND | ARM64_XREF_TYPE_MASK_BC_COND | ARM64_XREF_TYPE_MASK_CBZ | ARM64_XREF_TYPE_MASK_CBNZ | ARM64_XREF_TYPE_MASK_TBZ | ARM64_XREF_TYPE_MASK_TBNZ),

    ARM64_XREF_TYPE_MASK_ADR = (1 << ARM64_XREF_TYPE_ADR),
    ARM64_XREF_TYPE_MASK_ADRP_ADD = (1 << ARM64_XREF_TYPE_ADRP_ADD),
    ARM64_XREF_TYPE_MASK_ADRP_LDR = (1 << ARM64_XREF_TYPE_ADRP_LDR),
    ARM64_XREF_TYPE_MASK_ADRP_STR = (1 << ARM64_XREF_TYPE_ADRP_STR),
    ARM64_XREF_TYPE_MASK_REFERENCE = (ARM64_XREF_TYPE_MASK_ADR | ARM64_XREF_TYPE_MASK_ADRP_ADD | ARM64_XREF_TYPE_MASK_ADRP_LDR | ARM64_XREF_TYPE_MASK_ADRP_STR),
    
    ARM64_XREF_TYPE_MASK_POINTER = (1 << ARM64_XREF_TYPE_POINTER),

    ARM64_XREF_TYPE_ALL = (ARM64_XREF_TYPE_MASK_CALL | ARM64_XREF_TYPE_MASK_JUMP | ARM64_XREF_TYPE_MASK_REFERENCE | ARM64_XREF_TYPE_MASK_POINTER),
} Arm64XrefTypeMask;

uint64_t pfsec_arm64_resolve_adrp_ldr_str_add_reference(PFSection *section, uint64_t adrpAddr, uint64_t ldrStrAddAddr);
uint64_t pfsec_arm64_resolve_adrp_ldr_str_add_reference_auto(PFSection *section, uint64_t ldrStrAddAddr);
uint64_t pfsec_arm64_resolve_stub(PFSection *section, uint64_t stubAddr);
void pfsec_arm64_enumerate_xrefs(PFSection *section, Arm64XrefTypeMask types, void (^xrefBlock)(Arm64XrefType type, uint64_t source, uint64_t target, bool *stop));
#endif