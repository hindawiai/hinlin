<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Derived from IRIX <sys/SN/SN0/sn0_fru.h>
 *
 * Copyright (C) 1992 - 1997, 1999 Silcon Graphics, Inc.
 * Copyright (C) 1999, 2006 Ralf Baechle (ralf@linux-mips)
 */
#अगर_अघोषित __ASM_SN_FRU_H
#घोषणा __ASM_SN_FRU_H

#घोषणा MAX_DIMMS			8	 /* max # of dimm banks */
#घोषणा MAX_PCIDEV			8	 /* max # of pci devices on a pci bus */

प्रकार अचिन्हित अक्षर confidence_t;

प्रकार काष्ठा kf_mem_s अणु
	confidence_t km_confidence; /* confidence level that the memory is bad
				     * is this necessary ?
				     */
	confidence_t km_dimm[MAX_DIMMS];
				    /* confidence level that dimm[i] is bad
				     *I think this is the right number
				     */

पूर्ण kf_mem_t;

प्रकार काष्ठा kf_cpu_s अणु
	confidence_t	kc_confidence; /* confidence level that cpu is bad */
	confidence_t	kc_icache; /* confidence level that instr. cache is bad */
	confidence_t	kc_dcache; /* confidence level that data   cache is bad */
	confidence_t	kc_scache; /* confidence level that sec.   cache is bad */
	confidence_t	kc_sysbus; /* confidence level that sysad/cmd/state bus is bad */
पूर्ण kf_cpu_t;

प्रकार काष्ठा kf_pci_bus_s अणु
	confidence_t	kpb_belief;	/* confidence level  that the  pci bus is bad */
	confidence_t	kpb_pcidev_belief[MAX_PCIDEV];
					/* confidence level that the pci dev is bad */
पूर्ण kf_pci_bus_t;

#पूर्ण_अगर /* __ASM_SN_FRU_H */
