<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2018 Netronome Systems, Inc. */

#समावेश <linux/bitfield.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>

#समावेश "nfp_net_ctrl.h"
#समावेश "nfp_net.h"

अटल व्योम nfp_net_tlv_caps_reset(काष्ठा nfp_net_tlv_caps *caps)
अणु
	स_रखो(caps, 0, माप(*caps));
	caps->me_freq_mhz = 1200;
	caps->mbox_off = NFP_NET_CFG_MBOX_BASE;
	caps->mbox_len = NFP_NET_CFG_MBOX_VAL_MAX_SZ;
पूर्ण

अटल bool
nfp_net_tls_parse_crypto_ops(काष्ठा device *dev, काष्ठा nfp_net_tlv_caps *caps,
			     u8 __iomem *ctrl_mem, u8 __iomem *data,
			     अचिन्हित पूर्णांक length, अचिन्हित पूर्णांक offset,
			     bool rx_stream_scan)
अणु
	/* Ignore the legacy TLV अगर new one was alपढ़ोy parsed */
	अगर (caps->tls_resync_ss && !rx_stream_scan)
		वापस true;

	अगर (length < 32) अणु
		dev_err(dev,
			"CRYPTO OPS TLV should be at least 32B, is %dB offset:%u\n",
			length, offset);
		वापस false;
	पूर्ण

	caps->crypto_ops = पढ़ोl(data);
	caps->crypto_enable_off = data - ctrl_mem + 16;
	caps->tls_resync_ss = rx_stream_scan;

	वापस true;
पूर्ण

पूर्णांक nfp_net_tlv_caps_parse(काष्ठा device *dev, u8 __iomem *ctrl_mem,
			   काष्ठा nfp_net_tlv_caps *caps)
अणु
	u8 __iomem *data = ctrl_mem + NFP_NET_CFG_TLV_BASE;
	u8 __iomem *end = ctrl_mem + NFP_NET_CFG_BAR_SZ;
	u32 hdr;

	nfp_net_tlv_caps_reset(caps);

	hdr = पढ़ोl(data);
	अगर (!hdr)
		वापस 0;

	जबतक (true) अणु
		अचिन्हित पूर्णांक length, offset;
		u32 hdr = पढ़ोl(data);

		length = FIELD_GET(NFP_NET_CFG_TLV_HEADER_LENGTH, hdr);
		offset = data - ctrl_mem;

		/* Advance past the header */
		data += 4;

		अगर (length % NFP_NET_CFG_TLV_LENGTH_INC) अणु
			dev_err(dev, "TLV size not multiple of %u offset:%u len:%u\n",
				NFP_NET_CFG_TLV_LENGTH_INC, offset, length);
			वापस -EINVAL;
		पूर्ण
		अगर (data + length > end) अणु
			dev_err(dev, "oversized TLV offset:%u len:%u\n",
				offset, length);
			वापस -EINVAL;
		पूर्ण

		चयन (FIELD_GET(NFP_NET_CFG_TLV_HEADER_TYPE, hdr)) अणु
		हाल NFP_NET_CFG_TLV_TYPE_UNKNOWN:
			dev_err(dev, "NULL TLV at offset:%u\n", offset);
			वापस -EINVAL;
		हाल NFP_NET_CFG_TLV_TYPE_RESERVED:
			अवरोध;
		हाल NFP_NET_CFG_TLV_TYPE_END:
			अगर (!length)
				वापस 0;

			dev_err(dev, "END TLV should be empty, has offset:%u len:%d\n",
				offset, length);
			वापस -EINVAL;
		हाल NFP_NET_CFG_TLV_TYPE_ME_FREQ:
			अगर (length != 4) अणु
				dev_err(dev,
					"ME FREQ TLV should be 4B, is %dB offset:%u\n",
					length, offset);
				वापस -EINVAL;
			पूर्ण

			caps->me_freq_mhz = पढ़ोl(data);
			अवरोध;
		हाल NFP_NET_CFG_TLV_TYPE_MBOX:
			अगर (!length) अणु
				caps->mbox_off = 0;
				caps->mbox_len = 0;
			पूर्ण अन्यथा अणु
				caps->mbox_off = data - ctrl_mem;
				caps->mbox_len = length;
			पूर्ण
			अवरोध;
		हाल NFP_NET_CFG_TLV_TYPE_EXPERIMENTAL0:
		हाल NFP_NET_CFG_TLV_TYPE_EXPERIMENTAL1:
			dev_warn(dev,
				 "experimental TLV type:%u offset:%u len:%u\n",
				 FIELD_GET(NFP_NET_CFG_TLV_HEADER_TYPE, hdr),
				 offset, length);
			अवरोध;
		हाल NFP_NET_CFG_TLV_TYPE_REPR_CAP:
			अगर (length < 4) अणु
				dev_err(dev, "REPR CAP TLV short %dB < 4B offset:%u\n",
					length, offset);
				वापस -EINVAL;
			पूर्ण

			caps->repr_cap = पढ़ोl(data);
			अवरोध;
		हाल NFP_NET_CFG_TLV_TYPE_MBOX_CMSG_TYPES:
			अगर (length >= 4)
				caps->mbox_cmsg_types = पढ़ोl(data);
			अवरोध;
		हाल NFP_NET_CFG_TLV_TYPE_CRYPTO_OPS:
			अगर (!nfp_net_tls_parse_crypto_ops(dev, caps, ctrl_mem,
							  data, length, offset,
							  false))
				वापस -EINVAL;
			अवरोध;
		हाल NFP_NET_CFG_TLV_TYPE_VNIC_STATS:
			अगर ((data - ctrl_mem) % 8) अणु
				dev_warn(dev, "VNIC STATS TLV misaligned, ignoring offset:%u len:%u\n",
					 offset, length);
				अवरोध;
			पूर्ण
			caps->vnic_stats_off = data - ctrl_mem;
			caps->vnic_stats_cnt = length / 10;
			अवरोध;
		हाल NFP_NET_CFG_TLV_TYPE_CRYPTO_OPS_RX_SCAN:
			अगर (!nfp_net_tls_parse_crypto_ops(dev, caps, ctrl_mem,
							  data, length, offset,
							  true))
				वापस -EINVAL;
			अवरोध;
		शेष:
			अगर (!FIELD_GET(NFP_NET_CFG_TLV_HEADER_REQUIRED, hdr))
				अवरोध;

			dev_err(dev, "unknown TLV type:%u offset:%u len:%u\n",
				FIELD_GET(NFP_NET_CFG_TLV_HEADER_TYPE, hdr),
				offset, length);
			वापस -EINVAL;
		पूर्ण

		data += length;
		अगर (data + 4 > end) अणु
			dev_err(dev, "reached end of BAR without END TLV\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Not reached */
	वापस -EINVAL;
पूर्ण
