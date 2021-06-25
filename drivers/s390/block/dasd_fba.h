<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Author(s)......: Holger Smolinski <Holger.Smolinski@de.ibm.com>
 * Bugreports.to..: <Linux390@de.ibm.com>
 * Copyright IBM Corp. 1999, 2000
 *
 */

#अगर_अघोषित DASD_FBA_H
#घोषणा DASD_FBA_H

/*
 * Maximum number of blocks to be chained
 */
#घोषणा DASD_FBA_MAX_BLOCKS		96

काष्ठा DE_fba_data अणु
	काष्ठा अणु
		अचिन्हित अक्षर perm:2;	/* Permissions on this extent */
		अचिन्हित अक्षर zero:2;	/* Must be zero */
		अचिन्हित अक्षर da:1;	/* usually zero */
		अचिन्हित अक्षर diag:1;	/* allow diagnose */
		अचिन्हित अक्षर zero2:2;	/* zero */
	पूर्ण __attribute__ ((packed)) mask;
	__u8 zero;		/* Must be zero */
	__u16 blk_size;		/* Blocksize */
	__u32 ext_loc;		/* Extent locator */
	__u32 ext_beg;		/* logical number of block 0 in extent */
	__u32 ext_end;		/* logocal number of last block in extent */
पूर्ण __attribute__ ((packed));

काष्ठा LO_fba_data अणु
	काष्ठा अणु
		अचिन्हित अक्षर zero:4;
		अचिन्हित अक्षर cmd:4;
	पूर्ण __attribute__ ((packed)) operation;
	__u8 auxiliary;
	__u16 blk_ct;
	__u32 blk_nr;
पूर्ण __attribute__ ((packed));

काष्ठा dasd_fba_अक्षरacteristics अणु
	जोड़ अणु
		__u8 c;
		काष्ठा अणु
			अचिन्हित अक्षर reserved:1;
			अचिन्हित अक्षर overrunnable:1;
			अचिन्हित अक्षर burst_byte:1;
			अचिन्हित अक्षर data_chain:1;
			अचिन्हित अक्षर zeros:4;
		पूर्ण __attribute__ ((packed)) bits;
	पूर्ण __attribute__ ((packed)) mode;
	जोड़ अणु
		__u8 c;
		काष्ठा अणु
			अचिन्हित अक्षर zero0:1;
			अचिन्हित अक्षर removable:1;
			अचिन्हित अक्षर shared:1;
			अचिन्हित अक्षर zero1:1;
			अचिन्हित अक्षर mam:1;
			अचिन्हित अक्षर zeros:3;
		पूर्ण __attribute__ ((packed)) bits;
	पूर्ण __attribute__ ((packed)) features;
	__u8 dev_class;
	__u8 unit_type;
	__u16 blk_size;
	__u32 blk_per_cycl;
	__u32 blk_per_bound;
	__u32 blk_bdsa;
	__u32 reserved0;
	__u16 reserved1;
	__u16 blk_ce;
	__u32 reserved2;
	__u16 reserved3;
पूर्ण __attribute__ ((packed));

#पूर्ण_अगर				/* DASD_FBA_H */
