<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
// Copyright (c) 2018 Mellanox Technologies

#समावेश <linux/hyperv.h>
#समावेश "mlx5_core.h"
#समावेश "lib/hv.h"

अटल पूर्णांक mlx5_hv_config_common(काष्ठा mlx5_core_dev *dev, व्योम *buf, पूर्णांक len,
				 पूर्णांक offset, bool पढ़ो)
अणु
	पूर्णांक rc = -EOPNOTSUPP;
	पूर्णांक bytes_वापसed;
	पूर्णांक block_id;

	अगर (offset % HV_CONFIG_BLOCK_SIZE_MAX || len != HV_CONFIG_BLOCK_SIZE_MAX)
		वापस -EINVAL;

	block_id = offset / HV_CONFIG_BLOCK_SIZE_MAX;

	rc = पढ़ो ?
	     hyperv_पढ़ो_cfg_blk(dev->pdev, buf,
				 HV_CONFIG_BLOCK_SIZE_MAX, block_id,
				 &bytes_वापसed) :
	     hyperv_ग_लिखो_cfg_blk(dev->pdev, buf,
				  HV_CONFIG_BLOCK_SIZE_MAX, block_id);

	/* Make sure len bytes were पढ़ो successfully  */
	अगर (पढ़ो && !rc && len != bytes_वापसed)
		rc = -EIO;

	अगर (rc) अणु
		mlx5_core_err(dev, "Failed to %s hv config, err = %d, len = %d, offset = %d\n",
			      पढ़ो ? "read" : "write", rc, len,
			      offset);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mlx5_hv_पढ़ो_config(काष्ठा mlx5_core_dev *dev, व्योम *buf, पूर्णांक len,
			पूर्णांक offset)
अणु
	वापस mlx5_hv_config_common(dev, buf, len, offset, true);
पूर्ण

पूर्णांक mlx5_hv_ग_लिखो_config(काष्ठा mlx5_core_dev *dev, व्योम *buf, पूर्णांक len,
			 पूर्णांक offset)
अणु
	वापस mlx5_hv_config_common(dev, buf, len, offset, false);
पूर्ण

पूर्णांक mlx5_hv_रेजिस्टर_invalidate(काष्ठा mlx5_core_dev *dev, व्योम *context,
				व्योम (*block_invalidate)(व्योम *context,
							 u64 block_mask))
अणु
	वापस hyperv_reg_block_invalidate(dev->pdev, context,
					   block_invalidate);
पूर्ण

व्योम mlx5_hv_unरेजिस्टर_invalidate(काष्ठा mlx5_core_dev *dev)
अणु
	hyperv_reg_block_invalidate(dev->pdev, शून्य, शून्य);
पूर्ण
