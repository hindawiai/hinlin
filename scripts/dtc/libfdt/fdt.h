<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-or-later OR BSD-2-Clause) */
#अगर_अघोषित FDT_H
#घोषणा FDT_H
/*
 * libfdt - Flat Device Tree manipulation
 * Copyright (C) 2006 David Gibson, IBM Corporation.
 * Copyright 2012 Kim Phillips, Freescale Semiconductor.
 */

#अगर_अघोषित __ASSEMBLY__

काष्ठा fdt_header अणु
	fdt32_t magic;			 /* magic word FDT_MAGIC */
	fdt32_t totalsize;		 /* total size of DT block */
	fdt32_t off_dt_काष्ठा;		 /* offset to काष्ठाure */
	fdt32_t off_dt_strings;		 /* offset to strings */
	fdt32_t off_mem_rsvmap;		 /* offset to memory reserve map */
	fdt32_t version;		 /* क्रमmat version */
	fdt32_t last_comp_version;	 /* last compatible version */

	/* version 2 fields below */
	fdt32_t boot_cpuid_phys;	 /* Which physical CPU id we're
					    booting on */
	/* version 3 fields below */
	fdt32_t size_dt_strings;	 /* size of the strings block */

	/* version 17 fields below */
	fdt32_t size_dt_काष्ठा;		 /* size of the काष्ठाure block */
पूर्ण;

काष्ठा fdt_reserve_entry अणु
	fdt64_t address;
	fdt64_t size;
पूर्ण;

काष्ठा fdt_node_header अणु
	fdt32_t tag;
	अक्षर name[0];
पूर्ण;

काष्ठा fdt_property अणु
	fdt32_t tag;
	fdt32_t len;
	fdt32_t nameoff;
	अक्षर data[0];
पूर्ण;

#पूर्ण_अगर /* !__ASSEMBLY */

#घोषणा FDT_MAGIC	0xd00dfeed	/* 4: version, 4: total size */
#घोषणा FDT_TAGSIZE	माप(fdt32_t)

#घोषणा FDT_BEGIN_NODE	0x1		/* Start node: full name */
#घोषणा FDT_END_NODE	0x2		/* End node */
#घोषणा FDT_PROP	0x3		/* Property: name off,
					   size, content */
#घोषणा FDT_NOP		0x4		/* nop */
#घोषणा FDT_END		0x9

#घोषणा FDT_V1_SIZE	(7*माप(fdt32_t))
#घोषणा FDT_V2_SIZE	(FDT_V1_SIZE + माप(fdt32_t))
#घोषणा FDT_V3_SIZE	(FDT_V2_SIZE + माप(fdt32_t))
#घोषणा FDT_V16_SIZE	FDT_V3_SIZE
#घोषणा FDT_V17_SIZE	(FDT_V16_SIZE + माप(fdt32_t))

#पूर्ण_अगर /* FDT_H */
