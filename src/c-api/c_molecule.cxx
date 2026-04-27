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
#include <gauxc/c/atom.h>
#include <gauxc/c/molecule.h>

#include <gauxc/atom.hpp>
#include <gauxc/molecule.hpp>

#include "c_molecule.hpp"
#include "c_status.hpp"
#include "api_logging.hpp"

namespace GauXC::C {

extern "C" {

GauXCMolecule gauxc_molecule_new(GauXCStatus* status) {
  GAUXC_API_LOG("gauxc_molecule_new()");
  detail::gauxc_status_init(status);
  GauXCMolecule mol{};
  mol.hdr = GauXCHeader{GauXC_Type_Molecule};
  mol.ptr = nullptr;

  try {
    mol.ptr = new Molecule();
  } catch (std::exception& e) {
    detail::gauxc_status_handle(status, 1, e.what());
  }
  return mol;
}

GauXCMolecule gauxc_molecule_new_from_atoms(GauXCStatus* status, const GauXCAtom* atoms, size_t natoms) {
  if (api_logging_enabled()) {
    fprintf(stderr, "[GAUXC_API] gauxc_molecule_new_from_atoms(natoms=%zu)\n", natoms);
    if (atoms != nullptr && natoms > 0) {
      fprintf(stderr, "[GAUXC_API]   Atom coordinates (Z, x, y, z):\n");
      for (size_t i = 0; i < natoms; ++i) {
        fprintf(stderr, "[GAUXC_API]     %2ld %12.6f %12.6f %12.6f\n",
          (long)atoms[i].Z, atoms[i].x, atoms[i].y, atoms[i].z);
      }
    }
  }
  detail::gauxc_status_init(status);
  GauXCMolecule mol{};
  mol.hdr = GauXCHeader{GauXC_Type_Molecule};
  mol.ptr = nullptr;
  if (atoms == nullptr || natoms == 0) {
    detail::gauxc_status_handle(status, 1, "Atom list is null or empty");
    return mol;
  }
  Molecule* mol_ptr = nullptr;

  try {
    mol_ptr = new Molecule();
    mol_ptr->reserve(natoms);
    for (size_t i = 0; i < natoms; ++i) {
      mol_ptr->push_back(detail::convert_atom(atoms[i]));
    }
    mol.ptr = mol_ptr;
  } catch (std::exception& e) {
    delete mol_ptr;
    detail::gauxc_status_handle(status, 1, e.what());
  }
  return mol;
}

void gauxc_molecule_delete(GauXCStatus* status, GauXCMolecule* mol) {
  GAUXC_API_LOG("gauxc_molecule_delete()");
  detail::gauxc_status_init(status);
  if (mol == nullptr) return;
  if (mol->ptr != nullptr)
    delete detail::get_molecule_ptr(*mol);
  mol->ptr = nullptr;
}

size_t gauxc_molecule_natoms(GauXCStatus* status, const GauXCMolecule mol) {
  GAUXC_API_LOG("gauxc_molecule_natoms()");
  detail::gauxc_status_init(status);
  if (mol.ptr == nullptr || mol.hdr.type != GauXC_Type_Molecule) {
    detail::gauxc_status_handle(status, 1, "Invalid Molecule handle");
    return 0;
  }
  return detail::get_molecule_ptr(mol)->natoms();
}

bool gauxc_molecule_equal(
  GauXCStatus* status,
  const GauXCMolecule mol_a,
  const GauXCMolecule mol_b
) {
  GAUXC_API_LOG("gauxc_molecule_equal()");
  detail::gauxc_status_init(status);
  if (mol_a.ptr == nullptr || mol_b.ptr == nullptr || mol_a.hdr.type != GauXC_Type_Molecule || mol_b.hdr.type != GauXC_Type_Molecule) {
    detail::gauxc_status_handle(status, 1, "Invalid Molecule handle");
    return false;
  }
  return *detail::get_molecule_ptr(mol_a) == *detail::get_molecule_ptr(mol_b);
}

} // extern "C"
} // namespace GauXC::C