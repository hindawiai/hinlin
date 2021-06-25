<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2018 Netronome Systems, Inc. */

#समावेश <linux/kernel.h>
#समावेश <net/devlink.h>

#समावेश "nfpcore/nfp_cpp.h"
#समावेश "nfpcore/nfp_nffw.h"
#समावेश "nfp_abi.h"
#समावेश "nfp_app.h"
#समावेश "nfp_main.h"

अटल u32 nfp_shared_buf_pool_unit(काष्ठा nfp_pf *pf, अचिन्हित पूर्णांक sb)
अणु
	__le32 sb_id = cpu_to_le32(sb);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < pf->num_shared_bufs; i++)
		अगर (pf->shared_bufs[i].id == sb_id)
			वापस le32_to_cpu(pf->shared_bufs[i].pool_size_unit);

	WARN_ON_ONCE(1);
	वापस 0;
पूर्ण

पूर्णांक nfp_shared_buf_pool_get(काष्ठा nfp_pf *pf, अचिन्हित पूर्णांक sb, u16 pool_index,
			    काष्ठा devlink_sb_pool_info *pool_info)
अणु
	काष्ठा nfp_shared_buf_pool_info_get get_data;
	काष्ठा nfp_shared_buf_pool_id id = अणु
		.shared_buf	= cpu_to_le32(sb),
		.pool		= cpu_to_le32(pool_index),
	पूर्ण;
	अचिन्हित पूर्णांक unit_size;
	पूर्णांक n;

	unit_size = nfp_shared_buf_pool_unit(pf, sb);
	अगर (!unit_size)
		वापस -EINVAL;

	n = nfp_mbox_cmd(pf, NFP_MBOX_POOL_GET, &id, माप(id),
			 &get_data, माप(get_data));
	अगर (n < 0)
		वापस n;
	अगर (n < माप(get_data))
		वापस -EIO;

	pool_info->pool_type = le32_to_cpu(get_data.pool_type);
	pool_info->threshold_type = le32_to_cpu(get_data.threshold_type);
	pool_info->size = le32_to_cpu(get_data.size) * unit_size;
	pool_info->cell_size = unit_size;

	वापस 0;
पूर्ण

पूर्णांक nfp_shared_buf_pool_set(काष्ठा nfp_pf *pf, अचिन्हित पूर्णांक sb,
			    u16 pool_index, u32 size,
			    क्रमागत devlink_sb_threshold_type threshold_type)
अणु
	काष्ठा nfp_shared_buf_pool_info_set set_data = अणु
		.id = अणु
			.shared_buf	= cpu_to_le32(sb),
			.pool		= cpu_to_le32(pool_index),
		पूर्ण,
		.threshold_type	= cpu_to_le32(threshold_type),
	पूर्ण;
	अचिन्हित पूर्णांक unit_size;

	unit_size = nfp_shared_buf_pool_unit(pf, sb);
	अगर (!unit_size || size % unit_size)
		वापस -EINVAL;
	set_data.size = cpu_to_le32(size / unit_size);

	वापस nfp_mbox_cmd(pf, NFP_MBOX_POOL_SET, &set_data, माप(set_data),
			    शून्य, 0);
पूर्ण

पूर्णांक nfp_shared_buf_रेजिस्टर(काष्ठा nfp_pf *pf)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(pf);
	अचिन्हित पूर्णांक i, num_entries, entry_sz;
	काष्ठा nfp_cpp_area *sb_desc_area;
	u8 __iomem *sb_desc;
	पूर्णांक n, err;

	अगर (!pf->mbox)
		वापस 0;

	n = nfp_pf_rtsym_पढ़ो_optional(pf, NFP_SHARED_BUF_COUNT_SYM_NAME, 0);
	अगर (n <= 0)
		वापस n;
	num_entries = n;

	sb_desc = nfp_pf_map_rtsym(pf, "sb_tbl", NFP_SHARED_BUF_TABLE_SYM_NAME,
				   num_entries * माप(pf->shared_bufs[0]),
				   &sb_desc_area);
	अगर (IS_ERR(sb_desc))
		वापस PTR_ERR(sb_desc);

	entry_sz = nfp_cpp_area_size(sb_desc_area) / num_entries;

	pf->shared_bufs = kदो_स्मृति_array(num_entries, माप(pf->shared_bufs[0]),
					GFP_KERNEL);
	अगर (!pf->shared_bufs) अणु
		err = -ENOMEM;
		जाओ err_release_area;
	पूर्ण

	क्रम (i = 0; i < num_entries; i++) अणु
		काष्ठा nfp_shared_buf *sb = &pf->shared_bufs[i];

		/* Entries may be larger in future FW */
		स_नकल_fromio(sb, sb_desc + i * entry_sz, माप(*sb));

		err = devlink_sb_रेजिस्टर(devlink,
					  le32_to_cpu(sb->id),
					  le32_to_cpu(sb->size),
					  le16_to_cpu(sb->ingress_pools_count),
					  le16_to_cpu(sb->egress_pools_count),
					  le16_to_cpu(sb->ingress_tc_count),
					  le16_to_cpu(sb->egress_tc_count));
		अगर (err)
			जाओ err_unreg_prev;
	पूर्ण
	pf->num_shared_bufs = num_entries;

	nfp_cpp_area_release_मुक्त(sb_desc_area);

	वापस 0;

err_unreg_prev:
	जबतक (i--)
		devlink_sb_unरेजिस्टर(devlink,
				      le32_to_cpu(pf->shared_bufs[i].id));
	kमुक्त(pf->shared_bufs);
err_release_area:
	nfp_cpp_area_release_मुक्त(sb_desc_area);
	वापस err;
पूर्ण

व्योम nfp_shared_buf_unरेजिस्टर(काष्ठा nfp_pf *pf)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(pf);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < pf->num_shared_bufs; i++)
		devlink_sb_unरेजिस्टर(devlink,
				      le32_to_cpu(pf->shared_bufs[i].id));
	kमुक्त(pf->shared_bufs);
पूर्ण
