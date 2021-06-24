<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2016  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#समावेश <linux/crc32.h>
#समावेश "qed.h"
#समावेश "qed_dev_api.h"
#समावेश "qed_mcp.h"
#समावेश "qed_sp.h"
#समावेश "qed_selftest.h"

पूर्णांक qed_selftest_memory(काष्ठा qed_dev *cdev)
अणु
	पूर्णांक rc = 0, i;

	क्रम_each_hwfn(cdev, i) अणु
		rc = qed_sp_heartbeat_ramrod(&cdev->hwfns[i]);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक qed_selftest_पूर्णांकerrupt(काष्ठा qed_dev *cdev)
अणु
	पूर्णांक rc = 0, i;

	क्रम_each_hwfn(cdev, i) अणु
		rc = qed_sp_heartbeat_ramrod(&cdev->hwfns[i]);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक qed_selftest_रेजिस्टर(काष्ठा qed_dev *cdev)
अणु
	काष्ठा qed_hwfn *p_hwfn;
	काष्ठा qed_ptt *p_ptt;
	पूर्णांक rc = 0, i;

	/* although perक्रमmed by MCP, this test is per engine */
	क्रम_each_hwfn(cdev, i) अणु
		p_hwfn = &cdev->hwfns[i];
		p_ptt = qed_ptt_acquire(p_hwfn);
		अगर (!p_ptt) अणु
			DP_ERR(p_hwfn, "failed to acquire ptt\n");
			वापस -EBUSY;
		पूर्ण
		rc = qed_mcp_bist_रेजिस्टर_test(p_hwfn, p_ptt);
		qed_ptt_release(p_hwfn, p_ptt);
		अगर (rc)
			अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक qed_selftest_घड़ी(काष्ठा qed_dev *cdev)
अणु
	काष्ठा qed_hwfn *p_hwfn;
	काष्ठा qed_ptt *p_ptt;
	पूर्णांक rc = 0, i;

	/* although perक्रमmed by MCP, this test is per engine */
	क्रम_each_hwfn(cdev, i) अणु
		p_hwfn = &cdev->hwfns[i];
		p_ptt = qed_ptt_acquire(p_hwfn);
		अगर (!p_ptt) अणु
			DP_ERR(p_hwfn, "failed to acquire ptt\n");
			वापस -EBUSY;
		पूर्ण
		rc = qed_mcp_bist_घड़ी_प्रकारest(p_hwfn, p_ptt);
		qed_ptt_release(p_hwfn, p_ptt);
		अगर (rc)
			अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक qed_selftest_nvram(काष्ठा qed_dev *cdev)
अणु
	काष्ठा qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_ptt *p_ptt = qed_ptt_acquire(p_hwfn);
	u32 num_images, i, j, nvm_crc, calc_crc;
	काष्ठा bist_nvm_image_att image_att;
	u8 *buf = शून्य;
	__be32 val;
	पूर्णांक rc;

	अगर (!p_ptt) अणु
		DP_ERR(p_hwfn, "failed to acquire ptt\n");
		वापस -EBUSY;
	पूर्ण

	/* Acquire from MFW the amount of available images */
	rc = qed_mcp_bist_nvm_get_num_images(p_hwfn, p_ptt, &num_images);
	अगर (rc || !num_images) अणु
		DP_ERR(p_hwfn, "Failed getting number of images\n");
		rc = -EINVAL;
		जाओ err0;
	पूर्ण

	/* Iterate over images and validate CRC */
	क्रम (i = 0; i < num_images; i++) अणु
		/* This mailbox वापसs inक्रमmation about the image required क्रम
		 * पढ़ोing it.
		 */
		rc = qed_mcp_bist_nvm_get_image_att(p_hwfn, p_ptt,
						    &image_att, i);
		अगर (rc) अणु
			DP_ERR(p_hwfn,
			       "Failed getting image index %d attributes\n",
			       i);
			जाओ err0;
		पूर्ण

		/* After MFW crash dump is collected - the image's CRC stops
		 * being valid.
		 */
		अगर (image_att.image_type == NVM_TYPE_MDUMP)
			जारी;

		DP_VERBOSE(p_hwfn, QED_MSG_SP, "image index %d, size %x\n",
			   i, image_att.len);

		/* Allocate a buffer क्रम holding the nvram image */
		buf = kzalloc(image_att.len, GFP_KERNEL);
		अगर (!buf) अणु
			rc = -ENOMEM;
			जाओ err0;
		पूर्ण

		/* Read image पूर्णांकo buffer */
		rc = qed_mcp_nvm_पढ़ो(p_hwfn->cdev, image_att.nvm_start_addr,
				      buf, image_att.len);
		अगर (rc) अणु
			DP_ERR(p_hwfn,
			       "Failed reading image index %d from nvm.\n", i);
			जाओ err1;
		पूर्ण

		/* Convert the buffer पूर्णांकo big-endian क्रमmat (excluding the
		 * closing 4 bytes of CRC).
		 */
		क्रम (j = 0; j < image_att.len - 4; j += 4) अणु
			val = cpu_to_be32(*(u32 *)&buf[j]);
			*(u32 *)&buf[j] = (__क्रमce u32)val;
		पूर्ण

		/* Calc CRC क्रम the "actual" image buffer, i.e. not including
		 * the last 4 CRC bytes.
		 */
		nvm_crc = *(u32 *)(buf + image_att.len - 4);
		calc_crc = crc32(0xffffffff, buf, image_att.len - 4);
		calc_crc = (__क्रमce u32)~cpu_to_be32(calc_crc);
		DP_VERBOSE(p_hwfn, QED_MSG_SP,
			   "nvm crc 0x%x, calc_crc 0x%x\n", nvm_crc, calc_crc);

		अगर (calc_crc != nvm_crc) अणु
			rc = -EINVAL;
			जाओ err1;
		पूर्ण

		/* Done with this image; Free to prevent द्विगुन release
		 * on subsequent failure.
		 */
		kमुक्त(buf);
		buf = शून्य;
	पूर्ण

	qed_ptt_release(p_hwfn, p_ptt);
	वापस 0;

err1:
	kमुक्त(buf);
err0:
	qed_ptt_release(p_hwfn, p_ptt);
	वापस rc;
पूर्ण
