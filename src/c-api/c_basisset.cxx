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
#include <exception>

#include <gauxc/c/shell.h>
#include <gauxc/c/basisset.h>

#include <gauxc/shell.hpp>
#include <gauxc/basisset.hpp>

#include "c_basisset.hpp"
#include "c_status.hpp"
#include "api_logging.hpp"

namespace GauXC::C {
namespace {

void log_shell_info(const GauXCShell* shells, size_t nshells, bool normalize) {
    if (!api_logging_enabled()) return;

    fprintf(stderr, "[GAUXC API] gauxc_basisset_new_from_shells()");
    fprintf(stderr, "[GAUXC_API] Creating BasisSet from %zu shells\n", nshells);
    fprintf(stderr, "[GAUXC_API]   Number of orbital shells: %zu\n", nshells);
    fprintf(stderr, "[GAUXC_API]   Number of primitive Cartesian functions: %d\n", (int)nshells);
    fprintf(stderr, "[GAUXC_API]   Norm type: %s\n\n", normalize ? "L2" : "None");

    fprintf(stderr, "[GAUXC_API] Shell data:\n");
    fprintf(stderr, "[GAUXC_API]  Shell      n    l   p/c   Origin (x, y, z)                      Tol         Exponent       Coefficient\n");

    for (size_t i = 0; i < nshells; ++i) {
        for (int p = 0; p < shells[i].nprim; ++p) {
            if (p == 0) {
                fprintf(stderr, "[GAUXC_API] %6zu %6d %4d  %2d/%2d  (%10.6f,%10.6f,%10.6f)  %10.2e  %14.10f  %14.10f\n",
                    i, shells[i].nprim, shells[i].l,
                    shells[i].pure ? 1 : 0, shells[i].pure ? 0 : 1,
                    shells[i].origin[0], shells[i].origin[1], shells[i].origin[2],
                    shells[i].shell_tolerance,
                    shells[i].exponents[p], shells[i].coefficients[p]);
            } else {
                fprintf(stderr, "[GAUXC_API]                                                                            %14.10f  %14.10f\n",
                    shells[i].exponents[p], shells[i].coefficients[p]);
            }
        }
    }
    fprintf(stderr, "\n");
}

}

extern "C" {

GauXCBasisSet gauxc_basisset_new(GauXCStatus* status) {
  GAUXC_API_LOG("gauxc_basisset_new()");
  detail::gauxc_status_init(status);
  GauXCBasisSet basis{};
  basis.hdr = GauXCHeader{GauXC_Type_BasisSet};
  basis.ptr = nullptr;
  try {
    basis.ptr = new BasisSet<double>();
  } catch (std::exception& e) {
    detail::gauxc_status_handle(status, 1, e.what());
  }
  return basis;
}

GauXCBasisSet gauxc_basisset_new_from_shells(GauXCStatus* status, const GauXCShell* shells, size_t nshells, bool normalize) {
  log_shell_info(shells, nshells, normalize);
  detail::gauxc_status_init(status);
  GauXCBasisSet basis{};
  basis.hdr = GauXCHeader{GauXC_Type_BasisSet};
  basis.ptr = nullptr;
  if (shells == nullptr || nshells == 0) {
    detail::gauxc_status_handle(status, 1, "Shell list is null or empty");
    return basis;
  }
  BasisSet<double>* basis_ptr = nullptr;
  try {
    basis_ptr = new BasisSet<double>();
    basis_ptr->reserve(nshells);
    for (size_t i = 0; i < nshells; ++i) {
      basis_ptr->push_back(detail::convert_shell(shells[i], normalize));
    }
    basis.ptr = basis_ptr;
  } catch (std::exception& e) {
    delete basis_ptr;
    detail::gauxc_status_handle(status, 1, e.what());
  }
  return basis;
}

void gauxc_basisset_delete(GauXCStatus* status, GauXCBasisSet* basis) {
  GAUXC_API_LOG("gauxc_basisset_delete(basis=%p)", (void*)basis);
  detail::gauxc_status_init(status);
  if (basis == nullptr) return;
  if (basis->ptr != nullptr)
    delete detail::get_basisset_ptr(*basis);
  basis->ptr = nullptr;
}

} // extern "C"
} // namespace GauXC::C
