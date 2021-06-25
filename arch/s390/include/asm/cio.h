<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Common पूर्णांकerface क्रम I/O on S/390
 */
#अगर_अघोषित _ASM_S390_CIO_H_
#घोषणा _ASM_S390_CIO_H_

#समावेश <linux/spinlock.h>
#समावेश <linux/bitops.h>
#समावेश <linux/genभाग.स>
#समावेश <यंत्र/types.h>

#घोषणा LPM_ANYPATH 0xff
#घोषणा __MAX_CSSID 0
#घोषणा __MAX_SUBCHANNEL 65535
#घोषणा __MAX_SSID 3

#समावेश <यंत्र/scsw.h>

/**
 * काष्ठा ccw1 - channel command word
 * @cmd_code: command code
 * @flags: flags, like IDA addressing, etc.
 * @count: byte count
 * @cda: data address
 *
 * The ccw is the basic काष्ठाure to build channel programs that perक्रमm
 * operations with the device or the control unit. Only Format-1 channel
 * command words are supported.
 */
काष्ठा ccw1 अणु
	__u8  cmd_code;
	__u8  flags;
	__u16 count;
	__u32 cda;
पूर्ण __attribute__ ((packed,aligned(8)));

/**
 * काष्ठा ccw0 - channel command word
 * @cmd_code: command code
 * @cda: data address
 * @flags: flags, like IDA addressing, etc.
 * @reserved: will be ignored
 * @count: byte count
 *
 * The क्रमmat-0 ccw काष्ठाure.
 */
काष्ठा ccw0 अणु
	__u8 cmd_code;
	__u32 cda : 24;
	__u8  flags;
	__u8  reserved;
	__u16 count;
पूर्ण __packed __aligned(8);

#घोषणा CCW_FLAG_DC		0x80
#घोषणा CCW_FLAG_CC		0x40
#घोषणा CCW_FLAG_SLI		0x20
#घोषणा CCW_FLAG_SKIP		0x10
#घोषणा CCW_FLAG_PCI		0x08
#घोषणा CCW_FLAG_IDA		0x04
#घोषणा CCW_FLAG_SUSPEND	0x02

#घोषणा CCW_CMD_READ_IPL	0x02
#घोषणा CCW_CMD_NOOP		0x03
#घोषणा CCW_CMD_BASIC_SENSE	0x04
#घोषणा CCW_CMD_TIC		0x08
#घोषणा CCW_CMD_STLCK           0x14
#घोषणा CCW_CMD_SENSE_PGID	0x34
#घोषणा CCW_CMD_SUSPEND_RECONN	0x5B
#घोषणा CCW_CMD_RDC		0x64
#घोषणा CCW_CMD_RELEASE		0x94
#घोषणा CCW_CMD_SET_PGID	0xAF
#घोषणा CCW_CMD_SENSE_ID	0xE4
#घोषणा CCW_CMD_DCTL		0xF3

#घोषणा SENSE_MAX_COUNT		0x20

/**
 * काष्ठा erw - extended report word
 * @res0: reserved
 * @auth: authorization check
 * @pvrf: path-verअगरication-required flag
 * @cpt: channel-path समयout
 * @fsavf: failing storage address validity flag
 * @cons: concurrent sense
 * @scavf: secondary ccw address validity flag
 * @fsaf: failing storage address क्रमmat
 * @scnt: sense count, अगर @cons == %1
 * @res16: reserved
 */
काष्ठा erw अणु
	__u32 res0  : 3;
	__u32 auth  : 1;
	__u32 pvrf  : 1;
	__u32 cpt   : 1;
	__u32 fsavf : 1;
	__u32 cons  : 1;
	__u32 scavf : 1;
	__u32 fsaf  : 1;
	__u32 scnt  : 6;
	__u32 res16 : 16;
पूर्ण __attribute__ ((packed));

/**
 * काष्ठा erw_eadm - EADM Subchannel extended report word
 * @b: aob error
 * @r: arsb error
 */
काष्ठा erw_eadm अणु
	__u32 : 16;
	__u32 b : 1;
	__u32 r : 1;
	__u32  : 14;
पूर्ण __packed;

/**
 * काष्ठा sublog - subchannel logout area
 * @res0: reserved
 * @esf: extended status flags
 * @lpum: last path used mask
 * @arep: ancillary report
 * @fvf: field-validity flags
 * @sacc: storage access code
 * @termc: termination code
 * @devsc: device-status check
 * @serr: secondary error
 * @ioerr: i/o-error alert
 * @seqc: sequence code
 */
काष्ठा sublog अणु
	__u32 res0  : 1;
	__u32 esf   : 7;
	__u32 lpum  : 8;
	__u32 arep  : 1;
	__u32 fvf   : 5;
	__u32 sacc  : 2;
	__u32 termc : 2;
	__u32 devsc : 1;
	__u32 serr  : 1;
	__u32 ioerr : 1;
	__u32 seqc  : 3;
पूर्ण __attribute__ ((packed));

/**
 * काष्ठा esw0 - Format 0 Extended Status Word (ESW)
 * @sublog: subchannel logout
 * @erw: extended report word
 * @faddr: failing storage address
 * @saddr: secondary ccw address
 */
काष्ठा esw0 अणु
	काष्ठा sublog sublog;
	काष्ठा erw erw;
	__u32  faddr[2];
	__u32  saddr;
पूर्ण __attribute__ ((packed));

/**
 * काष्ठा esw1 - Format 1 Extended Status Word (ESW)
 * @zero0: reserved zeros
 * @lpum: last path used mask
 * @zero16: reserved zeros
 * @erw: extended report word
 * @zeros: three fullwords of zeros
 */
काष्ठा esw1 अणु
	__u8  zero0;
	__u8  lpum;
	__u16 zero16;
	काष्ठा erw erw;
	__u32 zeros[3];
पूर्ण __attribute__ ((packed));

/**
 * काष्ठा esw2 - Format 2 Extended Status Word (ESW)
 * @zero0: reserved zeros
 * @lpum: last path used mask
 * @dcti: device-connect-समय पूर्णांकerval
 * @erw: extended report word
 * @zeros: three fullwords of zeros
 */
काष्ठा esw2 अणु
	__u8  zero0;
	__u8  lpum;
	__u16 dcti;
	काष्ठा erw erw;
	__u32 zeros[3];
पूर्ण __attribute__ ((packed));

/**
 * काष्ठा esw3 - Format 3 Extended Status Word (ESW)
 * @zero0: reserved zeros
 * @lpum: last path used mask
 * @res: reserved
 * @erw: extended report word
 * @zeros: three fullwords of zeros
 */
काष्ठा esw3 अणु
	__u8  zero0;
	__u8  lpum;
	__u16 res;
	काष्ठा erw erw;
	__u32 zeros[3];
पूर्ण __attribute__ ((packed));

/**
 * काष्ठा esw_eadm - EADM Subchannel Extended Status Word (ESW)
 * @sublog: subchannel logout
 * @erw: extended report word
 */
काष्ठा esw_eadm अणु
	__u32 sublog;
	काष्ठा erw_eadm erw;
	__u32 : 32;
	__u32 : 32;
	__u32 : 32;
पूर्ण __packed;

/**
 * काष्ठा irb - पूर्णांकerruption response block
 * @scsw: subchannel status word
 * @esw: extended status word
 * @ecw: extended control word
 *
 * The irb that is handed to the device driver when an पूर्णांकerrupt occurs. For
 * solicited पूर्णांकerrupts, the common I/O layer alपढ़ोy perक्रमms checks whether
 * a field is valid; a field not being valid is always passed as %0.
 * If a unit check occurred, @ecw may contain sense data; this is retrieved
 * by the common I/O layer itself अगर the device करोesn't support concurrent
 * sense (so that the device driver never needs to perक्रमm basic sense itself).
 * For unsolicited पूर्णांकerrupts, the irb is passed as-is (expect क्रम sense data,
 * अगर applicable).
 */
काष्ठा irb अणु
	जोड़ scsw scsw;
	जोड़ अणु
		काष्ठा esw0 esw0;
		काष्ठा esw1 esw1;
		काष्ठा esw2 esw2;
		काष्ठा esw3 esw3;
		काष्ठा esw_eadm eadm;
	पूर्ण esw;
	__u8   ecw[32];
पूर्ण __attribute__ ((packed,aligned(4)));

/**
 * काष्ठा ciw - command inक्रमmation word  (CIW) layout
 * @et: entry type
 * @reserved: reserved bits
 * @ct: command type
 * @cmd: command code
 * @count: command count
 */
काष्ठा ciw अणु
	__u32 et       :  2;
	__u32 reserved :  2;
	__u32 ct       :  4;
	__u32 cmd      :  8;
	__u32 count    : 16;
पूर्ण __attribute__ ((packed));

#घोषणा CIW_TYPE_RCD	0x0    	/* पढ़ो configuration data */
#घोषणा CIW_TYPE_SII	0x1    	/* set पूर्णांकerface identअगरier */
#घोषणा CIW_TYPE_RNI	0x2    	/* पढ़ो node identअगरier */

/*
 * Node Descriptor as defined in SA22-7204, "Common I/O-Device Commands"
 */

#घोषणा ND_VALIDITY_VALID	0
#घोषणा ND_VALIDITY_OUTDATED	1
#घोषणा ND_VALIDITY_INVALID	2

काष्ठा node_descriptor अणु
	/* Flags. */
	जोड़ अणु
		काष्ठा अणु
			u32 validity:3;
			u32 reserved:5;
		पूर्ण __packed;
		u8 byte0;
	पूर्ण __packed;

	/* Node parameters. */
	u32 params:24;

	/* Node ID. */
	अक्षर type[6];
	अक्षर model[3];
	अक्षर manufacturer[3];
	अक्षर plant[2];
	अक्षर seq[12];
	u16 tag;
पूर्ण __packed;

/*
 * Flags used as input parameters क्रम करो_IO()
 */
#घोषणा DOIO_ALLOW_SUSPEND	 0x0001 /* allow क्रम channel prog. suspend */
#घोषणा DOIO_DENY_PREFETCH	 0x0002 /* करोn't allow क्रम CCW prefetch */
#घोषणा DOIO_SUPPRESS_INTER	 0x0004 /* suppress पूर्णांकermediate पूर्णांकer. */
					/* ... क्रम suspended CCWs */
/* Device or subchannel gone. */
#घोषणा CIO_GONE       0x0001
/* No path to device. */
#घोषणा CIO_NO_PATH    0x0002
/* Device has appeared. */
#घोषणा CIO_OPER       0x0004
/* Sick revalidation of device. */
#घोषणा CIO_REVALIDATE 0x0008
/* Device did not respond in समय. */
#घोषणा CIO_BOXED      0x0010

/**
 * काष्ठा ccw_dev_id - unique identअगरier क्रम ccw devices
 * @ssid: subchannel set id
 * @devno: device number
 *
 * This काष्ठाure is not directly based on any hardware काष्ठाure. The
 * hardware identअगरies a device by its device number and its subchannel,
 * which is in turn identअगरied by its id. In order to get a unique identअगरier
 * क्रम ccw devices across subchannel sets, @काष्ठा ccw_dev_id has been
 * पूर्णांकroduced.
 */
काष्ठा ccw_dev_id अणु
	u8 ssid;
	u16 devno;
पूर्ण;

/**
 * ccw_dev_id_is_equal() - compare two ccw_dev_ids
 * @dev_id1: a ccw_dev_id
 * @dev_id2: another ccw_dev_id
 * Returns:
 *  %1 अगर the two काष्ठाures are equal field-by-field,
 *  %0 अगर not.
 * Context:
 *  any
 */
अटल अंतरभूत पूर्णांक ccw_dev_id_is_equal(काष्ठा ccw_dev_id *dev_id1,
				      काष्ठा ccw_dev_id *dev_id2)
अणु
	अगर ((dev_id1->ssid == dev_id2->ssid) &&
	    (dev_id1->devno == dev_id2->devno))
		वापस 1;
	वापस 0;
पूर्ण

/**
 * pathmask_to_pos() - find the position of the left-most bit in a pathmask
 * @mask: pathmask with at least one bit set
 */
अटल अंतरभूत u8 pathmask_to_pos(u8 mask)
अणु
	वापस 8 - ffs(mask);
पूर्ण

बाह्य व्योम css_schedule_reprobe(व्योम);

बाह्य व्योम *cio_dma_zalloc(माप_प्रकार size);
बाह्य व्योम cio_dma_मुक्त(व्योम *cpu_addr, माप_प्रकार size);
बाह्य काष्ठा device *cio_get_dma_css_dev(व्योम);

व्योम *cio_gp_dma_zalloc(काष्ठा gen_pool *gp_dma, काष्ठा device *dma_dev,
			माप_प्रकार size);
व्योम cio_gp_dma_मुक्त(काष्ठा gen_pool *gp_dma, व्योम *cpu_addr, माप_प्रकार size);
व्योम cio_gp_dma_destroy(काष्ठा gen_pool *gp_dma, काष्ठा device *dma_dev);
काष्ठा gen_pool *cio_gp_dma_create(काष्ठा device *dma_dev, पूर्णांक nr_pages);

/* Function from drivers/s390/cio/chsc.c */
पूर्णांक chsc_sstpc(व्योम *page, अचिन्हित पूर्णांक op, u16 ctrl, u64 *घड़ी_delta);
पूर्णांक chsc_sstpi(व्योम *page, व्योम *result, माप_प्रकार size);
पूर्णांक chsc_stzi(व्योम *page, व्योम *result, माप_प्रकार size);
पूर्णांक chsc_sgib(u32 origin);
पूर्णांक chsc_scud(u16 cu, u64 *esm, u8 *esm_valid);

#पूर्ण_अगर
