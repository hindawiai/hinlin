<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright(c) 2009 Intel Corporation. All rights reserved.
 *
 * Maपूर्णांकained at www.Open-FCoE.org
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/crc32.h>
#समावेश <linux/module.h>

#समावेश <scsi/libfc.h>

#समावेश "fc_encode.h"
#समावेश "fc_libfc.h"

MODULE_AUTHOR("Open-FCoE.org");
MODULE_DESCRIPTION("libfc");
MODULE_LICENSE("GPL v2");

अचिन्हित पूर्णांक fc_debug_logging;
module_param_named(debug_logging, fc_debug_logging, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(debug_logging, "a bit mask of logging levels");

DEFINE_MUTEX(fc_prov_mutex);
अटल LIST_HEAD(fc_local_ports);
काष्ठा blocking_notअगरier_head fc_lport_notअगरier_head =
		BLOCKING_NOTIFIER_INIT(fc_lport_notअगरier_head);
EXPORT_SYMBOL(fc_lport_notअगरier_head);

/*
 * Providers which primarily send requests and PRLIs.
 */
काष्ठा fc4_prov *fc_active_prov[FC_FC4_PROV_SIZE] = अणु
	[0] = &fc_rport_t0_prov,
	[FC_TYPE_FCP] = &fc_rport_fcp_init,
पूर्ण;

/*
 * Providers which receive requests.
 */
काष्ठा fc4_prov *fc_passive_prov[FC_FC4_PROV_SIZE] = अणु
	[FC_TYPE_ELS] = &fc_lport_els_prov,
पूर्ण;

/**
 * libfc_init() - Initialize libfc.ko
 */
अटल पूर्णांक __init libfc_init(व्योम)
अणु
	पूर्णांक rc = 0;

	rc = fc_setup_fcp();
	अगर (rc)
		वापस rc;

	rc = fc_setup_exch_mgr();
	अगर (rc)
		जाओ destroy_pkt_cache;

	rc = fc_setup_rport();
	अगर (rc)
		जाओ destroy_em;

	वापस rc;
destroy_em:
	fc_destroy_exch_mgr();
destroy_pkt_cache:
	fc_destroy_fcp();
	वापस rc;
पूर्ण
module_init(libfc_init);

/**
 * libfc_निकास() - Tear करोwn libfc.ko
 */
अटल व्योम __निकास libfc_निकास(व्योम)
अणु
	fc_destroy_fcp();
	fc_destroy_exch_mgr();
	fc_destroy_rport();
पूर्ण
module_निकास(libfc_निकास);

/**
 * fc_copy_buffer_to_sglist() - This routine copies the data of a buffer
 *				पूर्णांकo a scatter-gather list (SG list).
 *
 * @buf: poपूर्णांकer to the data buffer.
 * @len: the byte-length of the data buffer.
 * @sg: poपूर्णांकer to the poपूर्णांकer of the SG list.
 * @nents: poपूर्णांकer to the reमुख्यing number of entries in the SG list.
 * @offset: poपूर्णांकer to the current offset in the SG list.
 * @crc: poपूर्णांकer to the 32-bit crc value.
 *	 If crc is शून्य, CRC is not calculated.
 */
u32 fc_copy_buffer_to_sglist(व्योम *buf, माप_प्रकार len,
			     काष्ठा scatterlist *sg,
			     u32 *nents, माप_प्रकार *offset,
			     u32 *crc)
अणु
	माप_प्रकार reमुख्यing = len;
	u32 copy_len = 0;

	जबतक (reमुख्यing > 0 && sg) अणु
		माप_प्रकार off, sg_bytes;
		व्योम *page_addr;

		अगर (*offset >= sg->length) अणु
			/*
			 * Check क्रम end and drop resources
			 * from the last iteration.
			 */
			अगर (!(*nents))
				अवरोध;
			--(*nents);
			*offset -= sg->length;
			sg = sg_next(sg);
			जारी;
		पूर्ण
		sg_bytes = min(reमुख्यing, sg->length - *offset);

		/*
		 * The scatterlist item may be bigger than PAGE_SIZE,
		 * but we are limited to mapping PAGE_SIZE at a समय.
		 */
		off = *offset + sg->offset;
		sg_bytes = min(sg_bytes,
			       (माप_प्रकार)(PAGE_SIZE - (off & ~PAGE_MASK)));
		page_addr = kmap_atomic(sg_page(sg) + (off >> PAGE_SHIFT));
		अगर (crc)
			*crc = crc32(*crc, buf, sg_bytes);
		स_नकल((अक्षर *)page_addr + (off & ~PAGE_MASK), buf, sg_bytes);
		kunmap_atomic(page_addr);
		buf += sg_bytes;
		*offset += sg_bytes;
		reमुख्यing -= sg_bytes;
		copy_len += sg_bytes;
	पूर्ण
	वापस copy_len;
पूर्ण

/**
 * fc_fill_hdr() -  fill FC header fields based on request
 * @fp: reply frame containing header to be filled in
 * @in_fp: request frame containing header to use in filling in reply
 * @r_ctl: R_CTL value क्रम header
 * @f_ctl: F_CTL value क्रम header, with 0 pad
 * @seq_cnt: sequence count क्रम the header, ignored अगर frame has a sequence
 * @parm_offset: parameter / offset value
 */
व्योम fc_fill_hdr(काष्ठा fc_frame *fp, स्थिर काष्ठा fc_frame *in_fp,
		 क्रमागत fc_rctl r_ctl, u32 f_ctl, u16 seq_cnt, u32 parm_offset)
अणु
	काष्ठा fc_frame_header *fh;
	काष्ठा fc_frame_header *in_fh;
	काष्ठा fc_seq *sp;
	u32 fill;

	fh = __fc_frame_header_get(fp);
	in_fh = __fc_frame_header_get(in_fp);

	अगर (f_ctl & FC_FC_END_SEQ) अणु
		fill = -fr_len(fp) & 3;
		अगर (fill) अणु
			/* TODO, this may be a problem with fragmented skb */
			skb_put_zero(fp_skb(fp), fill);
			f_ctl |= fill;
		पूर्ण
		fr_eof(fp) = FC_खातापूर्ण_T;
	पूर्ण अन्यथा अणु
		WARN_ON(fr_len(fp) % 4 != 0);	/* no pad to non last frame */
		fr_eof(fp) = FC_खातापूर्ण_N;
	पूर्ण

	fh->fh_r_ctl = r_ctl;
	स_नकल(fh->fh_d_id, in_fh->fh_s_id, माप(fh->fh_d_id));
	स_नकल(fh->fh_s_id, in_fh->fh_d_id, माप(fh->fh_s_id));
	fh->fh_type = in_fh->fh_type;
	hton24(fh->fh_f_ctl, f_ctl);
	fh->fh_ox_id = in_fh->fh_ox_id;
	fh->fh_rx_id = in_fh->fh_rx_id;
	fh->fh_cs_ctl = 0;
	fh->fh_df_ctl = 0;
	fh->fh_parm_offset = htonl(parm_offset);

	sp = fr_seq(in_fp);
	अगर (sp) अणु
		fr_seq(fp) = sp;
		fh->fh_seq_id = sp->id;
		seq_cnt = sp->cnt;
	पूर्ण अन्यथा अणु
		fh->fh_seq_id = 0;
	पूर्ण
	fh->fh_seq_cnt = ntohs(seq_cnt);
	fr_sof(fp) = seq_cnt ? FC_SOF_N3 : FC_SOF_I3;
	fr_encaps(fp) = fr_encaps(in_fp);
पूर्ण
EXPORT_SYMBOL(fc_fill_hdr);

/**
 * fc_fill_reply_hdr() -  fill FC reply header fields based on request
 * @fp: reply frame containing header to be filled in
 * @in_fp: request frame containing header to use in filling in reply
 * @r_ctl: R_CTL value क्रम reply
 * @parm_offset: parameter / offset value
 */
व्योम fc_fill_reply_hdr(काष्ठा fc_frame *fp, स्थिर काष्ठा fc_frame *in_fp,
		       क्रमागत fc_rctl r_ctl, u32 parm_offset)
अणु
	काष्ठा fc_seq *sp;

	sp = fr_seq(in_fp);
	अगर (sp)
		fr_seq(fp) = fc_seq_start_next(sp);
	fc_fill_hdr(fp, in_fp, r_ctl, FC_FCTL_RESP, 0, parm_offset);
पूर्ण
EXPORT_SYMBOL(fc_fill_reply_hdr);

/**
 * fc_fc4_conf_lport_params() - Modअगरy "service_params" of specअगरied lport
 * अगर there is service provider (target provider) रेजिस्टरed with libfc
 * क्रम specअगरied "fc_ft_type"
 * @lport: Local port which service_params needs to be modअगरied
 * @type: FC-4 type, such as FC_TYPE_FCP
 */
व्योम fc_fc4_conf_lport_params(काष्ठा fc_lport *lport, क्रमागत fc_fh_type type)
अणु
	काष्ठा fc4_prov *prov_entry;
	BUG_ON(type >= FC_FC4_PROV_SIZE);
	BUG_ON(!lport);
	prov_entry = fc_passive_prov[type];
	अगर (type == FC_TYPE_FCP) अणु
		अगर (prov_entry && prov_entry->recv)
			lport->service_params |= FCP_SPPF_TARG_FCN;
	पूर्ण
पूर्ण

व्योम fc_lport_iterate(व्योम (*notअगरy)(काष्ठा fc_lport *, व्योम *), व्योम *arg)
अणु
	काष्ठा fc_lport *lport;

	mutex_lock(&fc_prov_mutex);
	list_क्रम_each_entry(lport, &fc_local_ports, lport_list)
		notअगरy(lport, arg);
	mutex_unlock(&fc_prov_mutex);
पूर्ण
EXPORT_SYMBOL(fc_lport_iterate);

/**
 * fc_fc4_रेजिस्टर_provider() - रेजिस्टर FC-4 upper-level provider.
 * @type: FC-4 type, such as FC_TYPE_FCP
 * @prov: काष्ठाure describing provider including ops vector.
 *
 * Returns 0 on success, negative error otherwise.
 */
पूर्णांक fc_fc4_रेजिस्टर_provider(क्रमागत fc_fh_type type, काष्ठा fc4_prov *prov)
अणु
	काष्ठा fc4_prov **prov_entry;
	पूर्णांक ret = 0;

	अगर (type >= FC_FC4_PROV_SIZE)
		वापस -EINVAL;
	mutex_lock(&fc_prov_mutex);
	prov_entry = (prov->recv ? fc_passive_prov : fc_active_prov) + type;
	अगर (*prov_entry)
		ret = -EBUSY;
	अन्यथा
		*prov_entry = prov;
	mutex_unlock(&fc_prov_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(fc_fc4_रेजिस्टर_provider);

/**
 * fc_fc4_deरेजिस्टर_provider() - deरेजिस्टर FC-4 upper-level provider.
 * @type: FC-4 type, such as FC_TYPE_FCP
 * @prov: काष्ठाure describing provider including ops vector.
 */
व्योम fc_fc4_deरेजिस्टर_provider(क्रमागत fc_fh_type type, काष्ठा fc4_prov *prov)
अणु
	BUG_ON(type >= FC_FC4_PROV_SIZE);
	mutex_lock(&fc_prov_mutex);
	अगर (prov->recv)
		RCU_INIT_POINTER(fc_passive_prov[type], शून्य);
	अन्यथा
		RCU_INIT_POINTER(fc_active_prov[type], शून्य);
	mutex_unlock(&fc_prov_mutex);
	synchronize_rcu();
पूर्ण
EXPORT_SYMBOL(fc_fc4_deरेजिस्टर_provider);

/**
 * fc_fc4_add_lport() - add new local port to list and run notअगरiers.
 * @lport:  The new local port.
 */
व्योम fc_fc4_add_lport(काष्ठा fc_lport *lport)
अणु
	mutex_lock(&fc_prov_mutex);
	list_add_tail(&lport->lport_list, &fc_local_ports);
	blocking_notअगरier_call_chain(&fc_lport_notअगरier_head,
				     FC_LPORT_EV_ADD, lport);
	mutex_unlock(&fc_prov_mutex);
पूर्ण

/**
 * fc_fc4_del_lport() - हटाओ local port from list and run notअगरiers.
 * @lport:  The new local port.
 */
व्योम fc_fc4_del_lport(काष्ठा fc_lport *lport)
अणु
	mutex_lock(&fc_prov_mutex);
	list_del(&lport->lport_list);
	blocking_notअगरier_call_chain(&fc_lport_notअगरier_head,
				     FC_LPORT_EV_DEL, lport);
	mutex_unlock(&fc_prov_mutex);
पूर्ण
