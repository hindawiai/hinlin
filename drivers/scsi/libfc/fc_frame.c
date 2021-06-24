<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright(c) 2007 Intel Corporation. All rights reserved.
 *
 * Maपूर्णांकained at www.Open-FCoE.org
 */

/*
 * Frame allocation.
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/crc32.h>
#समावेश <linux/gfp.h>

#समावेश <scsi/fc_frame.h>

/*
 * Check the CRC in a frame.
 */
u32 fc_frame_crc_check(काष्ठा fc_frame *fp)
अणु
	u32 crc;
	u32 error;
	स्थिर u8 *bp;
	अचिन्हित पूर्णांक len;

	WARN_ON(!fc_frame_is_linear(fp));
	fr_flags(fp) &= ~FCPHF_CRC_UNCHECKED;
	len = (fr_len(fp) + 3) & ~3;	/* round up length to include fill */
	bp = (स्थिर u8 *) fr_hdr(fp);
	crc = ~crc32(~0, bp, len);
	error = crc ^ fr_crc(fp);
	वापस error;
पूर्ण
EXPORT_SYMBOL(fc_frame_crc_check);

/*
 * Allocate a frame पूर्णांकended to be sent.
 * Get an sk_buff क्रम the frame and set the length.
 */
काष्ठा fc_frame *_fc_frame_alloc(माप_प्रकार len)
अणु
	काष्ठा fc_frame *fp;
	काष्ठा sk_buff *skb;

	WARN_ON((len % माप(u32)) != 0);
	len += माप(काष्ठा fc_frame_header);
	skb = alloc_skb_fclone(len + FC_FRAME_HEADROOM + FC_FRAME_TAILROOM +
			       NET_SKB_PAD, GFP_ATOMIC);
	अगर (!skb)
		वापस शून्य;
	skb_reserve(skb, NET_SKB_PAD + FC_FRAME_HEADROOM);
	fp = (काष्ठा fc_frame *) skb;
	fc_frame_init(fp);
	skb_put(skb, len);
	वापस fp;
पूर्ण
EXPORT_SYMBOL(_fc_frame_alloc);

काष्ठा fc_frame *fc_frame_alloc_fill(काष्ठा fc_lport *lp, माप_प्रकार payload_len)
अणु
	काष्ठा fc_frame *fp;
	माप_प्रकार fill;

	fill = payload_len % 4;
	अगर (fill != 0)
		fill = 4 - fill;
	fp = _fc_frame_alloc(payload_len + fill);
	अगर (fp) अणु
		स_रखो((अक्षर *) fr_hdr(fp) + payload_len, 0, fill);
		/* trim is OK, we just allocated it so there are no fragments */
		skb_trim(fp_skb(fp),
			 payload_len + माप(काष्ठा fc_frame_header));
	पूर्ण
	वापस fp;
पूर्ण
EXPORT_SYMBOL(fc_frame_alloc_fill);
