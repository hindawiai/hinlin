<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *    tape device discipline क्रम 3590 tapes.
 *
 *    Copyright IBM Corp. 2001, 2006
 *    Author(s): Stefan Bader <shbader@de.ibm.com>
 *		 Michael Holzheu <holzheu@de.ibm.com>
 *		 Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#अगर_अघोषित _TAPE_3590_H
#घोषणा _TAPE_3590_H

#घोषणा MEDIUM_SENSE	0xc2
#घोषणा READ_PREVIOUS	0x0a
#घोषणा MODE_SENSE	0xcf
#घोषणा PERFORM_SS_FUNC 0x77
#घोषणा READ_SS_DATA	0x3e

#घोषणा PREP_RD_SS_DATA 0x18
#घोषणा RD_ATTMSG	0x3

#घोषणा SENSE_BRA_PER  0
#घोषणा SENSE_BRA_CONT 1
#घोषणा SENSE_BRA_RE   2
#घोषणा SENSE_BRA_DRE  3

#घोषणा SENSE_FMT_LIBRARY	0x23
#घोषणा SENSE_FMT_UNSOLICITED	0x40
#घोषणा SENSE_FMT_COMMAND_REJ	0x41
#घोषणा SENSE_FMT_COMMAND_EXEC0 0x50
#घोषणा SENSE_FMT_COMMAND_EXEC1 0x51
#घोषणा SENSE_FMT_EVENT0	0x60
#घोषणा SENSE_FMT_EVENT1	0x61
#घोषणा SENSE_FMT_MIM		0x70
#घोषणा SENSE_FMT_SIM		0x71

#घोषणा MSENSE_UNASSOCIATED	 0x00
#घोषणा MSENSE_ASSOCIATED_MOUNT	 0x01
#घोषणा MSENSE_ASSOCIATED_UMOUNT 0x02
#घोषणा MSENSE_CRYPT_MASK	 0x00000010

#घोषणा TAPE_3590_MAX_MSG	 0xb0

/* Datatypes */

काष्ठा tape_3590_disc_data अणु
	काष्ठा tape390_crypt_info crypt_info;
	पूर्णांक पढ़ो_back_op;
पूर्ण;

#घोषणा TAPE_3590_CRYPT_INFO(device) \
	((काष्ठा tape_3590_disc_data*)(device->discdata))->crypt_info
#घोषणा TAPE_3590_READ_BACK_OP(device) \
	((काष्ठा tape_3590_disc_data*)(device->discdata))->पढ़ो_back_op

काष्ठा tape_3590_sense अणु

	अचिन्हित पूर्णांक command_rej:1;
	अचिन्हित पूर्णांक पूर्णांकerv_req:1;
	अचिन्हित पूर्णांक bus_out_check:1;
	अचिन्हित पूर्णांक eq_check:1;
	अचिन्हित पूर्णांक data_check:1;
	अचिन्हित पूर्णांक overrun:1;
	अचिन्हित पूर्णांक def_unit_check:1;
	अचिन्हित पूर्णांक assgnd_अन्यथाw:1;

	अचिन्हित पूर्णांक locate_fail:1;
	अचिन्हित पूर्णांक inst_online:1;
	अचिन्हित पूर्णांक reserved:1;
	अचिन्हित पूर्णांक blk_seq_err:1;
	अचिन्हित पूर्णांक begin_part:1;
	अचिन्हित पूर्णांक wr_mode:1;
	अचिन्हित पूर्णांक wr_prot:1;
	अचिन्हित पूर्णांक not_cap:1;

	अचिन्हित पूर्णांक bra:2;
	अचिन्हित पूर्णांक lc:3;
	अचिन्हित पूर्णांक vlf_active:1;
	अचिन्हित पूर्णांक sपंचांग:1;
	अचिन्हित पूर्णांक med_pos:1;

	अचिन्हित पूर्णांक rac:8;

	अचिन्हित पूर्णांक rc_rqc:16;

	अचिन्हित पूर्णांक mc:8;

	अचिन्हित पूर्णांक sense_fmt:8;

	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक emc:4;
			अचिन्हित पूर्णांक smc:4;
			अचिन्हित पूर्णांक sev:2;
			अचिन्हित पूर्णांक reserved:6;
			अचिन्हित पूर्णांक md:8;
			अचिन्हित पूर्णांक refcode:8;
			अचिन्हित पूर्णांक mid:16;
			अचिन्हित पूर्णांक mp:16;
			अचिन्हित अक्षर volid[6];
			अचिन्हित पूर्णांक fid:8;
		पूर्ण f70;
		काष्ठा अणु
			अचिन्हित पूर्णांक emc:4;
			अचिन्हित पूर्णांक smc:4;
			अचिन्हित पूर्णांक sev:2;
			अचिन्हित पूर्णांक reserved1:5;
			अचिन्हित पूर्णांक mdf:1;
			अचिन्हित अक्षर md[3];
			अचिन्हित पूर्णांक simid:8;
			अचिन्हित पूर्णांक uid:16;
			अचिन्हित पूर्णांक refcode1:16;
			अचिन्हित पूर्णांक refcode2:16;
			अचिन्हित पूर्णांक refcode3:16;
			अचिन्हित पूर्णांक reserved2:8;
		पूर्ण f71;
		अचिन्हित अक्षर data[14];
	पूर्ण fmt;
	अचिन्हित अक्षर pad[10];

पूर्ण __attribute__ ((packed));

काष्ठा tape_3590_med_sense अणु
	अचिन्हित पूर्णांक macst:4;
	अचिन्हित पूर्णांक masst:4;
	अक्षर pad1[7];
	अचिन्हित पूर्णांक flags;
	अक्षर pad2[116];
पूर्ण __attribute__ ((packed));

काष्ठा tape_3590_rdc_data अणु
	अक्षर data[64];
पूर्ण __attribute__ ((packed));

/* Dataकाष्ठाures क्रम 3592 encryption support */

काष्ठा tape3592_kekl अणु
	__u8 flags;
	अक्षर label[64];
पूर्ण __attribute__ ((packed));

काष्ठा tape3592_kekl_pair अणु
	__u8 count;
	काष्ठा tape3592_kekl kekl[2];
पूर्ण __attribute__ ((packed));

काष्ठा tape3592_kekl_query_data अणु
	__u16 len;
	__u8  fmt;
	__u8  mc;
	__u32 id;
	__u8  flags;
	काष्ठा tape3592_kekl_pair kekls;
	अक्षर reserved[116];
पूर्ण __attribute__ ((packed));

काष्ठा tape3592_kekl_query_order अणु
	__u8 code;
	__u8 flags;
	अक्षर reserved1[2];
	__u8 max_count;
	अक्षर reserved2[35];
पूर्ण __attribute__ ((packed));

काष्ठा tape3592_kekl_set_order अणु
	__u8 code;
	__u8 flags;
	अक्षर reserved1[2];
	__u8 op;
	काष्ठा tape3592_kekl_pair kekls;
	अक्षर reserved2[120];
पूर्ण __attribute__ ((packed));

#पूर्ण_अगर /* _TAPE_3590_H */
