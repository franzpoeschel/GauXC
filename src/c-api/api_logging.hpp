/**
 * GauXC Copyright (c) 2020-2024, The Regents of the University of California,
 * through Lawrence Berkeley National Laboratory (subject to receipt of
 * any required approvals from the U.S. Dept. of Energy).
 *
 * (c) 2024-2025, Microsoft Corporation
 *
 * All rights reserved.
 *
 * See LICENSE.txt for details
 */

#ifndef GAUXC_API_LOGGING_HPP
#define GAUXC_API_LOGGING_HPP

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <gauxc/c/enums.h>

namespace GauXC {
namespace detail {

using namespace GauXC::C;

inline const char* execution_space_name(GauXC_ExecutionSpace es) {
    switch(es) {
        case GauXC_ExecutionSpace_Host:  return "Host";
        case GauXC_ExecutionSpace_Device: return "Device";
        default: return "Unknown";
    }
}

inline const char* radial_quad_name(GauXC_RadialQuad rq) {
    switch(rq) {
        case GauXC_RadialQuad_Becke:             return "Becke";
        case GauXC_RadialQuad_MuraKnowles:       return "MuraKnowles";
        case GauXC_RadialQuad_MurrayHandyLaming: return "MurrayHandyLaming";
        case GauXC_RadialQuad_TreutlerAhlrichs:  return "TreutlerAhlrichs";
        default: return "Unknown";
    }
}

inline const char* atomic_grid_size_name(GauXC_AtomicGridSizeDefault ags) {
    switch(ags) {
        case GauXC_AtomicGridSizeDefault_FineGrid:      return "FineGrid";
        case GauXC_AtomicGridSizeDefault_UltraFineGrid: return "UltraFineGrid";
        case GauXC_AtomicGridSizeDefault_SuperFineGrid: return "SuperFineGrid";
        case GauXC_AtomicGridSizeDefault_GM3:           return "GM3";
        case GauXC_AtomicGridSizeDefault_GM5:           return "GM5";
        default: return "Unknown";
    }
}

inline const char* xc_weight_alg_name(GauXC_XCWeightAlg alg) {
    switch(alg) {
        case GauXC_XCWeightAlg_NOTPARTITIONED: return "NotPartitioned";
        case GauXC_XCWeightAlg_Becke: return "Becke";
        case GauXC_XCWeightAlg_SSF:   return "SSF";
        case GauXC_XCWeightAlg_LKO:   return "LKO";
        default: return "Unknown";
    }
}

inline const char* pruning_scheme_name(GauXC_PruningScheme ps) {
    switch(ps) {
        case GauXC_PruningScheme_Unpruned: return "Unpruned";
        case GauXC_PruningScheme_Robust:   return "Robust";
        case GauXC_PruningScheme_Treutler: return "Treutler";
        default: return "Unknown";
    }
}

inline const char* basis_norm_type_name(int norm_type) {
    switch(norm_type) {
        case 1: return "L1";
        case 2: return "L2";
        case 3: return "LInf";
        default: return "Unknown";
    }
}

inline const char* shell_type_name(int l) {
    switch(l) {
        case 0: return "s";
        case 1: return "p";
        case 2: return "d";
        case 3: return "f";
        case 4: return "g";
        case 5: return "h";
        case 6: return "i";
        default: return "?";
    }
}

inline const char* functional_enum_name(int func_enum) {
    switch(func_enum) {
        case 0: return "SVWN3";
        case 1: return "SVWN5";
        case 2: return "BLYP";
        case 3: return "B3LYP";
        case 4: return "PBE";
        case 5: return "revPBE";
        case 6: return "PBE0";
        case 7: return "SCAN";
        case 8: return "R2SCAN";
        case 9: return "R2SCANL";
        case 10: return "M062X";
        case 11: return "PKZB";
        case 12: return "EPC17_1";
        case 13: return "EPC17_2";
        case 14: return "EPC18_1";
        case 15: return "EPC18_2";
        case 16: return "B97D";
        case 17: return "B97D3ZERO";
        case 18: return "CAMB3LYP";
        case 19: return "LDA";
        case 20: return "M06L";
        case 21: return "SCAN0";
        case 22: return "SPW92";
        case 23: return "TPSS";
        case 24: return "TPSSh";
        case 25: return "TPSS0";
        case 26: return "VWN3";
        case 27: return "VWN5";
        case 28: return "LRCwPBE";
        case 29: return "LRCwPBEh";
        case 30: return "BP86";
        case 31: return "HSE03";
        case 32: return "HSE06";
        case 33: return "revB3LYP";
        case 34: return "revPBE0";
        case 35: return "revTPSS";
        case 36: return "revTPSSh";
        case 37: return "PW91";
        case 38: return "mBEEF";
        case 39: return "B3PW91";
        case 40: return "O3LYP";
        case 41: return "OLYP";
        case 42: return "OPBE";
        case 43: return "mPW1K";
        case 44: return "RPBE";
        case 45: return "B88";
        case 46: return "MPW91";
        case 47: return "RSCAN";
        case 48: return "TUNEDCAMB3LYP";
        case 49: return "wB97";
        case 50: return "wB97X";
        case 51: return "wB97XD";
        case 52: return "wB97XD3";
        case 53: return "LCwPBE";
        case 54: return "X3LYP";
        case 55: return "XLYP";
        case 56: return "BHANDH";
        case 57: return "BMK";
        case 58: return "BP86VWN";
        case 59: return "PW86B95";
        case 60: return "PW86PBE";
        case 61: return "R2SCAN0";
        case 62: return "R2SCANh";
        case 63: return "R2SCAN50";
        case 64: return "M05";
        case 65: return "M06";
        case 66: return "M08HX";
        case 67: return "M08SO";
        case 68: return "M052X";
        case 69: return "M06SX";
        case 70: return "CF22D";
        case 71: return "SOGGA11X";
        case 72: return "M06HF";
        case 73: return "M11";
        case 74: return "MN12L";
        case 75: return "MN12SX";
        case 76: return "MN15";
        case 77: return "MN15L";
        case 78: return "revM06L";
        default: return "Unknown";
    }
}

}

static inline bool api_logging_enabled() {
    static bool enabled = ([]() {
        const char* env_val = std::getenv("GAUXC_LOG_API_CALLS");
        return env_val && (std::strcmp(env_val, "1") == 0 || std::strcmp(env_val, "true") == 0);
    })();
    return enabled;
}

#define GAUXC_API_LOG(...) \
    do { \
        if (GauXC::api_logging_enabled()) { \
            std::fprintf(stderr, "[GAUXC_API] " __VA_ARGS__); \
            std::fprintf(stderr, "\n"); \
        } \
    } while(0)

#define GAUXC_API_LOG_SCOPED(...) \
    do { \
        if (GauXC::api_logging_enabled()) { \
            std::fprintf(stderr, "[GAUXC_API] " __VA_ARGS__); \
            std::fprintf(stderr, "\n"); \
        } \
    } while(0)

}

#endif // GAUXC_API_LOGGING_HPP