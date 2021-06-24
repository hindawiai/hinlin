<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright(c) 2007 Intel Corporation. All rights reserved.
 *
 * Maपूर्णांकained at www.Open-FCoE.org
 */

#अगर_अघोषित _FC_FRAME_H_
#घोषणा _FC_FRAME_H_

#समावेश <linux/scatterlist.h>
#समावेश <linux/skbuff.h>
#समावेश <scsi/scsi_cmnd.h>

#समावेश <scsi/fc/fc_fs.h>
#समावेश <scsi/fc/fc_fcp.h>
#समावेश <scsi/fc/fc_encaps.h>

#समावेश <linux/अगर_ether.h>

/* some helpful macros */

#घोषणा ntohll(x) be64_to_cpu(x)
#घोषणा htonll(x) cpu_to_be64(x)

अटल अंतरभूत u32 ntoh24(स्थिर u8 *p)
अणु
	वापस (p[0] << 16) | (p[1] << 8) | p[2];
पूर्ण

अटल अंतरभूत व्योम hton24(u8 *p, u32 v)
अणु
	p[0] = (v >> 16) & 0xff;
	p[1] = (v >> 8) & 0xff;
	p[2] = v & 0xff;
पूर्ण

/*
 * The fc_frame पूर्णांकerface is used to pass frame data between functions.
 * The frame includes the data buffer, length, and SOF / खातापूर्ण delimiter types.
 * A poपूर्णांकer to the port काष्ठाure of the receiving port is also includeded.
 */

#घोषणा	FC_FRAME_HEADROOM	32	/* headroom क्रम VLAN + FCoE headers */
#घोषणा	FC_FRAME_TAILROOM	8	/* trailer space क्रम FCoE */

/* Max number of skb frags allowed, reserving one क्रम fcoe_crc_eof page */
#घोषणा FC_FRAME_SG_LEN		(MAX_SKB_FRAGS - 1)

#घोषणा fp_skb(fp)	(&((fp)->skb))
#घोषणा fr_hdr(fp)	((fp)->skb.data)
#घोषणा fr_len(fp)	((fp)->skb.len)
#घोषणा fr_cb(fp)	((काष्ठा fcoe_rcv_info *)&((fp)->skb.cb[0]))
#घोषणा fr_dev(fp)	(fr_cb(fp)->fr_dev)
#घोषणा fr_seq(fp)	(fr_cb(fp)->fr_seq)
#घोषणा fr_sof(fp)	(fr_cb(fp)->fr_sof)
#घोषणा fr_eof(fp)	(fr_cb(fp)->fr_eof)
#घोषणा fr_flags(fp)	(fr_cb(fp)->fr_flags)
#घोषणा fr_encaps(fp)	(fr_cb(fp)->fr_encaps)
#घोषणा fr_max_payload(fp)	(fr_cb(fp)->fr_max_payload)
#घोषणा fr_fsp(fp)	(fr_cb(fp)->fr_fsp)
#घोषणा fr_crc(fp)	(fr_cb(fp)->fr_crc)

काष्ठा fc_frame अणु
	काष्ठा sk_buff skb;
पूर्ण;

काष्ठा fcoe_rcv_info अणु
	काष्ठा fc_lport	*fr_dev;	/* transport layer निजी poपूर्णांकer */
	काष्ठा fc_seq	*fr_seq;	/* क्रम use with exchange manager */
	काष्ठा fc_fcp_pkt *fr_fsp;	/* क्रम the corresponding fcp I/O */
	u32		fr_crc;
	u16		fr_max_payload;	/* max FC payload */
	u8		fr_sof;		/* start of frame delimiter */
	u8		fr_eof;		/* end of frame delimiter */
	u8		fr_flags;	/* flags - see below */
	u8		fr_encaps;	/* LLD encapsulation info (e.g. FIP) */
	u8		granted_mac[ETH_ALEN]; /* FCoE MAC address */
पूर्ण;


/*
 * Get fc_frame poपूर्णांकer क्रम an skb that's alपढ़ोy been imported.
 */
अटल अंतरभूत काष्ठा fcoe_rcv_info *fcoe_dev_from_skb(स्थिर काष्ठा sk_buff *skb)
अणु
	BUILD_BUG_ON(माप(काष्ठा fcoe_rcv_info) > माप(skb->cb));
	वापस (काष्ठा fcoe_rcv_info *) skb->cb;
पूर्ण

/*
 * fr_flags.
 */
#घोषणा	FCPHF_CRC_UNCHECKED	0x01	/* CRC not computed, still appended */

/*
 * Initialize a frame.
 * We करोn't करो a complete स_रखो here क्रम perक्रमmance reasons.
 * The caller must set fr_मुक्त, fr_hdr, fr_len, fr_sof, and fr_eof eventually.
 */
अटल अंतरभूत व्योम fc_frame_init(काष्ठा fc_frame *fp)
अणु
	fr_dev(fp) = शून्य;
	fr_seq(fp) = शून्य;
	fr_flags(fp) = 0;
	fr_encaps(fp) = 0;
पूर्ण

काष्ठा fc_frame *fc_frame_alloc_fill(काष्ठा fc_lport *, माप_प्रकार payload_len);
काष्ठा fc_frame *_fc_frame_alloc(माप_प्रकार payload_len);

/*
 * Allocate fc_frame काष्ठाure and buffer.  Set the initial length to
 * payload_size + माप (काष्ठा fc_frame_header).
 */
अटल अंतरभूत काष्ठा fc_frame *fc_frame_alloc(काष्ठा fc_lport *dev, माप_प्रकार len)
अणु
	काष्ठा fc_frame *fp;

	/*
	 * Note: Since len will often be a स्थिरant multiple of 4,
	 * this check will usually be evaluated and eliminated at compile समय.
	 */
	अगर (len && len % 4)
		fp = fc_frame_alloc_fill(dev, len);
	अन्यथा
		fp = _fc_frame_alloc(len);
	वापस fp;
पूर्ण

/*
 * Free the fc_frame काष्ठाure and buffer.
 */
अटल अंतरभूत व्योम fc_frame_मुक्त(काष्ठा fc_frame *fp)
अणु
	kमुक्त_skb(fp_skb(fp));
पूर्ण

अटल अंतरभूत पूर्णांक fc_frame_is_linear(काष्ठा fc_frame *fp)
अणु
	वापस !skb_is_nonlinear(fp_skb(fp));
पूर्ण

/*
 * Get frame header from message in fc_frame काष्ठाure.
 * This version करोesn't करो a length check.
 */
अटल अंतरभूत
काष्ठा fc_frame_header *__fc_frame_header_get(स्थिर काष्ठा fc_frame *fp)
अणु
	वापस (काष्ठा fc_frame_header *)fr_hdr(fp);
पूर्ण

/*
 * Get frame header from message in fc_frame काष्ठाure.
 * This hides a cast and provides a place to add some checking.
 */
अटल अंतरभूत
काष्ठा fc_frame_header *fc_frame_header_get(स्थिर काष्ठा fc_frame *fp)
अणु
	WARN_ON(fr_len(fp) < माप(काष्ठा fc_frame_header));
	वापस __fc_frame_header_get(fp);
पूर्ण

/*
 * Get source FC_ID (S_ID) from frame header in message.
 */
अटल अंतरभूत u32 fc_frame_sid(स्थिर काष्ठा fc_frame *fp)
अणु
	वापस ntoh24(__fc_frame_header_get(fp)->fh_s_id);
पूर्ण

/*
 * Get destination FC_ID (D_ID) from frame header in message.
 */
अटल अंतरभूत u32 fc_frame_did(स्थिर काष्ठा fc_frame *fp)
अणु
	वापस ntoh24(__fc_frame_header_get(fp)->fh_d_id);
पूर्ण

/*
 * Get frame payload from message in fc_frame काष्ठाure.
 * This hides a cast and provides a place to add some checking.
 * The len parameter is the minimum length क्रम the payload portion.
 * Returns शून्य अगर the frame is too लघु.
 *
 * This assumes the पूर्णांकeresting part of the payload is in the first part
 * of the buffer क्रम received data.  This may not be appropriate to use क्रम
 * buffers being transmitted.
 */
अटल अंतरभूत व्योम *fc_frame_payload_get(स्थिर काष्ठा fc_frame *fp,
					 माप_प्रकार len)
अणु
	व्योम *pp = शून्य;

	अगर (fr_len(fp) >= माप(काष्ठा fc_frame_header) + len)
		pp = fc_frame_header_get(fp) + 1;
	वापस pp;
पूर्ण

/*
 * Get frame payload opcode (first byte) from message in fc_frame काष्ठाure.
 * This hides a cast and provides a place to add some checking. Return 0
 * अगर the frame has no payload.
 */
अटल अंतरभूत u8 fc_frame_payload_op(स्थिर काष्ठा fc_frame *fp)
अणु
	u8 *cp;

	cp = fc_frame_payload_get(fp, माप(u8));
	अगर (!cp)
		वापस 0;
	वापस *cp;

पूर्ण

/*
 * Get FC class from frame.
 */
अटल अंतरभूत क्रमागत fc_class fc_frame_class(स्थिर काष्ठा fc_frame *fp)
अणु
	वापस fc_sof_class(fr_sof(fp));
पूर्ण

/*
 * Check the CRC in a frame.
 * The CRC immediately follows the last data item *AFTER* the length.
 * The वापस value is zero अगर the CRC matches.
 */
u32 fc_frame_crc_check(काष्ठा fc_frame *);

अटल अंतरभूत u8 fc_frame_rctl(स्थिर काष्ठा fc_frame *fp)
अणु
	वापस fc_frame_header_get(fp)->fh_r_ctl;
पूर्ण

अटल अंतरभूत bool fc_frame_is_cmd(स्थिर काष्ठा fc_frame *fp)
अणु
	वापस fc_frame_rctl(fp) == FC_RCTL_DD_UNSOL_CMD;
पूर्ण

/*
 * Check क्रम leaks.
 * Prपूर्णांक the frame header of any currently allocated frame, assuming there
 * should be none at this poपूर्णांक.
 */
व्योम fc_frame_leak_check(व्योम);

अटल अंतरभूत व्योम __fc_fill_fc_hdr(काष्ठा fc_frame_header *fh,
				    क्रमागत fc_rctl r_ctl,
				    u32 did, u32 sid, क्रमागत fc_fh_type type,
				    u32 f_ctl, u32 parm_offset)
अणु
	WARN_ON(r_ctl == 0);
	fh->fh_r_ctl = r_ctl;
	hton24(fh->fh_d_id, did);
	hton24(fh->fh_s_id, sid);
	fh->fh_type = type;
	hton24(fh->fh_f_ctl, f_ctl);
	fh->fh_cs_ctl = 0;
	fh->fh_df_ctl = 0;
	fh->fh_parm_offset = htonl(parm_offset);
पूर्ण

/**
 * fill FC header fields in specअगरied fc_frame
 */
अटल अंतरभूत व्योम fc_fill_fc_hdr(काष्ठा fc_frame *fp, क्रमागत fc_rctl r_ctl,
				  u32 did, u32 sid, क्रमागत fc_fh_type type,
				  u32 f_ctl, u32 parm_offset)
अणु
	काष्ठा fc_frame_header *fh;

	fh = fc_frame_header_get(fp);
	__fc_fill_fc_hdr(fh, r_ctl, did, sid, type, f_ctl, parm_offset);
पूर्ण


#पूर्ण_अगर /* _FC_FRAME_H_ */
