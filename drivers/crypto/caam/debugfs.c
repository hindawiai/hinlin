<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/* Copyright 2019 NXP */

#समावेश <linux/debugfs.h>
#समावेश "compat.h"
#समावेश "debugfs.h"
#समावेश "regs.h"
#समावेश "intern.h"

अटल पूर्णांक caam_debugfs_u64_get(व्योम *data, u64 *val)
अणु
	*val = caam64_to_cpu(*(u64 *)data);
	वापस 0;
पूर्ण

अटल पूर्णांक caam_debugfs_u32_get(व्योम *data, u64 *val)
अणु
	*val = caam32_to_cpu(*(u32 *)data);
	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(caam_fops_u32_ro, caam_debugfs_u32_get, शून्य, "%llu\n");
DEFINE_DEBUGFS_ATTRIBUTE(caam_fops_u64_ro, caam_debugfs_u64_get, शून्य, "%llu\n");

#अगर_घोषित CONFIG_CAAM_QI
/*
 * This is a counter क्रम the number of बार the congestion group (where all
 * the request and response queueus are) reached congestion. Incremented
 * each समय the congestion callback is called with congested == true.
 */
अटल u64 बार_congested;

व्योम caam_debugfs_qi_congested(व्योम)
अणु
	बार_congested++;
पूर्ण

व्योम caam_debugfs_qi_init(काष्ठा caam_drv_निजी *ctrlpriv)
अणु
	debugfs_create_file("qi_congested", 0444, ctrlpriv->ctl,
			    &बार_congested, &caam_fops_u64_ro);
पूर्ण
#पूर्ण_अगर

व्योम caam_debugfs_init(काष्ठा caam_drv_निजी *ctrlpriv, काष्ठा dentry *root)
अणु
	काष्ठा caam_perfmon *perfmon;

	/*
	 * FIXME: needs better naming distinction, as some amalgamation of
	 * "caam" and nprop->full_name. The OF name isn't distinctive,
	 * but करोes separate instances
	 */
	perfmon = (काष्ठा caam_perfmon __क्रमce *)&ctrlpriv->ctrl->perfmon;

	ctrlpriv->ctl = debugfs_create_dir("ctl", root);

	debugfs_create_file("rq_dequeued", 0444, ctrlpriv->ctl,
			    &perfmon->req_dequeued, &caam_fops_u64_ro);
	debugfs_create_file("ob_rq_encrypted", 0444, ctrlpriv->ctl,
			    &perfmon->ob_enc_req, &caam_fops_u64_ro);
	debugfs_create_file("ib_rq_decrypted", 0444, ctrlpriv->ctl,
			    &perfmon->ib_dec_req, &caam_fops_u64_ro);
	debugfs_create_file("ob_bytes_encrypted", 0444, ctrlpriv->ctl,
			    &perfmon->ob_enc_bytes, &caam_fops_u64_ro);
	debugfs_create_file("ob_bytes_protected", 0444, ctrlpriv->ctl,
			    &perfmon->ob_prot_bytes, &caam_fops_u64_ro);
	debugfs_create_file("ib_bytes_decrypted", 0444, ctrlpriv->ctl,
			    &perfmon->ib_dec_bytes, &caam_fops_u64_ro);
	debugfs_create_file("ib_bytes_validated", 0444, ctrlpriv->ctl,
			    &perfmon->ib_valid_bytes, &caam_fops_u64_ro);

	/* Controller level - global status values */
	debugfs_create_file("fault_addr", 0444, ctrlpriv->ctl,
			    &perfmon->faultaddr, &caam_fops_u32_ro);
	debugfs_create_file("fault_detail", 0444, ctrlpriv->ctl,
			    &perfmon->faultdetail, &caam_fops_u32_ro);
	debugfs_create_file("fault_status", 0444, ctrlpriv->ctl,
			    &perfmon->status, &caam_fops_u32_ro);

	/* Internal covering keys (useful in non-secure mode only) */
	ctrlpriv->ctl_kek_wrap.data = (__क्रमce व्योम *)&ctrlpriv->ctrl->kek[0];
	ctrlpriv->ctl_kek_wrap.size = KEK_KEY_SIZE * माप(u32);
	debugfs_create_blob("kek", 0444, ctrlpriv->ctl,
			    &ctrlpriv->ctl_kek_wrap);

	ctrlpriv->ctl_tkek_wrap.data = (__क्रमce व्योम *)&ctrlpriv->ctrl->tkek[0];
	ctrlpriv->ctl_tkek_wrap.size = KEK_KEY_SIZE * माप(u32);
	debugfs_create_blob("tkek", 0444, ctrlpriv->ctl,
			    &ctrlpriv->ctl_tkek_wrap);

	ctrlpriv->ctl_tdsk_wrap.data = (__क्रमce व्योम *)&ctrlpriv->ctrl->tdsk[0];
	ctrlpriv->ctl_tdsk_wrap.size = KEK_KEY_SIZE * माप(u32);
	debugfs_create_blob("tdsk", 0444, ctrlpriv->ctl,
			    &ctrlpriv->ctl_tdsk_wrap);
पूर्ण
