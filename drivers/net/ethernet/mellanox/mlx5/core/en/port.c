<शैली गुरु>
/*
 * Copyright (c) 2018, Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश "port.h"

/* speed in units of 1Mb */
अटल स्थिर u32 mlx5e_link_speed[MLX5E_LINK_MODES_NUMBER] = अणु
	[MLX5E_1000BASE_CX_SGMII] = 1000,
	[MLX5E_1000BASE_KX]       = 1000,
	[MLX5E_10GBASE_CX4]       = 10000,
	[MLX5E_10GBASE_KX4]       = 10000,
	[MLX5E_10GBASE_KR]        = 10000,
	[MLX5E_20GBASE_KR2]       = 20000,
	[MLX5E_40GBASE_CR4]       = 40000,
	[MLX5E_40GBASE_KR4]       = 40000,
	[MLX5E_56GBASE_R4]        = 56000,
	[MLX5E_10GBASE_CR]        = 10000,
	[MLX5E_10GBASE_SR]        = 10000,
	[MLX5E_10GBASE_ER]        = 10000,
	[MLX5E_40GBASE_SR4]       = 40000,
	[MLX5E_40GBASE_LR4]       = 40000,
	[MLX5E_50GBASE_SR2]       = 50000,
	[MLX5E_100GBASE_CR4]      = 100000,
	[MLX5E_100GBASE_SR4]      = 100000,
	[MLX5E_100GBASE_KR4]      = 100000,
	[MLX5E_100GBASE_LR4]      = 100000,
	[MLX5E_100BASE_TX]        = 100,
	[MLX5E_1000BASE_T]        = 1000,
	[MLX5E_10GBASE_T]         = 10000,
	[MLX5E_25GBASE_CR]        = 25000,
	[MLX5E_25GBASE_KR]        = 25000,
	[MLX5E_25GBASE_SR]        = 25000,
	[MLX5E_50GBASE_CR2]       = 50000,
	[MLX5E_50GBASE_KR2]       = 50000,
पूर्ण;

अटल स्थिर u32 mlx5e_ext_link_speed[MLX5E_EXT_LINK_MODES_NUMBER] = अणु
	[MLX5E_SGMII_100M]			= 100,
	[MLX5E_1000BASE_X_SGMII]		= 1000,
	[MLX5E_5GBASE_R]			= 5000,
	[MLX5E_10GBASE_XFI_XAUI_1]		= 10000,
	[MLX5E_40GBASE_XLAUI_4_XLPPI_4]		= 40000,
	[MLX5E_25GAUI_1_25GBASE_CR_KR]		= 25000,
	[MLX5E_50GAUI_2_LAUI_2_50GBASE_CR2_KR2]	= 50000,
	[MLX5E_50GAUI_1_LAUI_1_50GBASE_CR_KR]	= 50000,
	[MLX5E_CAUI_4_100GBASE_CR4_KR4]		= 100000,
	[MLX5E_100GAUI_2_100GBASE_CR2_KR2]	= 100000,
	[MLX5E_200GAUI_4_200GBASE_CR4_KR4]	= 200000,
	[MLX5E_400GAUI_8]			= 400000,
	[MLX5E_100GAUI_1_100GBASE_CR_KR]	= 100000,
	[MLX5E_200GAUI_2_200GBASE_CR2_KR2]	= 200000,
	[MLX5E_400GAUI_4_400GBASE_CR4_KR4]	= 400000,
पूर्ण;

bool mlx5e_ptys_ext_supported(काष्ठा mlx5_core_dev *mdev)
अणु
	काष्ठा mlx5e_port_eth_proto eproto;
	पूर्णांक err;

	अगर (MLX5_CAP_PCAM_FEATURE(mdev, ptys_extended_ethernet))
		वापस true;

	err = mlx5_port_query_eth_proto(mdev, 1, true, &eproto);
	अगर (err)
		वापस false;

	वापस !!eproto.cap;
पूर्ण

अटल व्योम mlx5e_port_get_speed_arr(काष्ठा mlx5_core_dev *mdev,
				     स्थिर u32 **arr, u32 *size,
				     bool क्रमce_legacy)
अणु
	bool ext = क्रमce_legacy ? false : mlx5e_ptys_ext_supported(mdev);

	*size = ext ? ARRAY_SIZE(mlx5e_ext_link_speed) :
		      ARRAY_SIZE(mlx5e_link_speed);
	*arr  = ext ? mlx5e_ext_link_speed : mlx5e_link_speed;
पूर्ण

पूर्णांक mlx5_port_query_eth_proto(काष्ठा mlx5_core_dev *dev, u8 port, bool ext,
			      काष्ठा mlx5e_port_eth_proto *eproto)
अणु
	u32 out[MLX5_ST_SZ_DW(ptys_reg)];
	पूर्णांक err;

	अगर (!eproto)
		वापस -EINVAL;

	err = mlx5_query_port_ptys(dev, out, माप(out), MLX5_PTYS_EN, port);
	अगर (err)
		वापस err;

	eproto->cap   = MLX5_GET_ETH_PROTO(ptys_reg, out, ext,
					   eth_proto_capability);
	eproto->admin = MLX5_GET_ETH_PROTO(ptys_reg, out, ext, eth_proto_admin);
	eproto->oper  = MLX5_GET_ETH_PROTO(ptys_reg, out, ext, eth_proto_oper);
	वापस 0;
पूर्ण

व्योम mlx5_port_query_eth_स्वतःneg(काष्ठा mlx5_core_dev *dev, u8 *an_status,
				 u8 *an_disable_cap, u8 *an_disable_admin)
अणु
	u32 out[MLX5_ST_SZ_DW(ptys_reg)];

	*an_status = 0;
	*an_disable_cap = 0;
	*an_disable_admin = 0;

	अगर (mlx5_query_port_ptys(dev, out, माप(out), MLX5_PTYS_EN, 1))
		वापस;

	*an_status = MLX5_GET(ptys_reg, out, an_status);
	*an_disable_cap = MLX5_GET(ptys_reg, out, an_disable_cap);
	*an_disable_admin = MLX5_GET(ptys_reg, out, an_disable_admin);
पूर्ण

पूर्णांक mlx5_port_set_eth_ptys(काष्ठा mlx5_core_dev *dev, bool an_disable,
			   u32 proto_admin, bool ext)
अणु
	u32 out[MLX5_ST_SZ_DW(ptys_reg)];
	u32 in[MLX5_ST_SZ_DW(ptys_reg)];
	u8 an_disable_admin;
	u8 an_disable_cap;
	u8 an_status;

	mlx5_port_query_eth_स्वतःneg(dev, &an_status, &an_disable_cap,
				    &an_disable_admin);
	अगर (!an_disable_cap && an_disable)
		वापस -EPERM;

	स_रखो(in, 0, माप(in));

	MLX5_SET(ptys_reg, in, local_port, 1);
	MLX5_SET(ptys_reg, in, an_disable_admin, an_disable);
	MLX5_SET(ptys_reg, in, proto_mask, MLX5_PTYS_EN);
	अगर (ext)
		MLX5_SET(ptys_reg, in, ext_eth_proto_admin, proto_admin);
	अन्यथा
		MLX5_SET(ptys_reg, in, eth_proto_admin, proto_admin);

	वापस mlx5_core_access_reg(dev, in, माप(in), out,
			    माप(out), MLX5_REG_PTYS, 0, 1);
पूर्ण

u32 mlx5e_port_ptys2speed(काष्ठा mlx5_core_dev *mdev, u32 eth_proto_oper,
			  bool क्रमce_legacy)
अणु
	अचिन्हित दीर्घ temp = eth_proto_oper;
	स्थिर u32 *table;
	u32 speed = 0;
	u32 max_size;
	पूर्णांक i;

	mlx5e_port_get_speed_arr(mdev, &table, &max_size, क्रमce_legacy);
	i = find_first_bit(&temp, max_size);
	अगर (i < max_size)
		speed = table[i];
	वापस speed;
पूर्ण

पूर्णांक mlx5e_port_linkspeed(काष्ठा mlx5_core_dev *mdev, u32 *speed)
अणु
	काष्ठा mlx5e_port_eth_proto eproto;
	bool क्रमce_legacy = false;
	bool ext;
	पूर्णांक err;

	ext = mlx5e_ptys_ext_supported(mdev);
	err = mlx5_port_query_eth_proto(mdev, 1, ext, &eproto);
	अगर (err)
		जाओ out;
	अगर (ext && !eproto.admin) अणु
		क्रमce_legacy = true;
		err = mlx5_port_query_eth_proto(mdev, 1, false, &eproto);
		अगर (err)
			जाओ out;
	पूर्ण
	*speed = mlx5e_port_ptys2speed(mdev, eproto.oper, क्रमce_legacy);
	अगर (!(*speed))
		err = -EINVAL;

out:
	वापस err;
पूर्ण

पूर्णांक mlx5e_port_max_linkspeed(काष्ठा mlx5_core_dev *mdev, u32 *speed)
अणु
	काष्ठा mlx5e_port_eth_proto eproto;
	u32 max_speed = 0;
	स्थिर u32 *table;
	u32 max_size;
	bool ext;
	पूर्णांक err;
	पूर्णांक i;

	ext = mlx5e_ptys_ext_supported(mdev);
	err = mlx5_port_query_eth_proto(mdev, 1, ext, &eproto);
	अगर (err)
		वापस err;

	mlx5e_port_get_speed_arr(mdev, &table, &max_size, false);
	क्रम (i = 0; i < max_size; ++i)
		अगर (eproto.cap & MLX5E_PROT_MASK(i))
			max_speed = max(max_speed, table[i]);

	*speed = max_speed;
	वापस 0;
पूर्ण

u32 mlx5e_port_speed2linkmodes(काष्ठा mlx5_core_dev *mdev, u32 speed,
			       bool क्रमce_legacy)
अणु
	u32 link_modes = 0;
	स्थिर u32 *table;
	u32 max_size;
	पूर्णांक i;

	mlx5e_port_get_speed_arr(mdev, &table, &max_size, क्रमce_legacy);
	क्रम (i = 0; i < max_size; ++i) अणु
		अगर (table[i] == speed)
			link_modes |= MLX5E_PROT_MASK(i);
	पूर्ण
	वापस link_modes;
पूर्ण

पूर्णांक mlx5e_port_query_pbmc(काष्ठा mlx5_core_dev *mdev, व्योम *out)
अणु
	पूर्णांक sz = MLX5_ST_SZ_BYTES(pbmc_reg);
	व्योम *in;
	पूर्णांक err;

	in = kzalloc(sz, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	MLX5_SET(pbmc_reg, in, local_port, 1);
	err = mlx5_core_access_reg(mdev, in, sz, out, sz, MLX5_REG_PBMC, 0, 0);

	kमुक्त(in);
	वापस err;
पूर्ण

पूर्णांक mlx5e_port_set_pbmc(काष्ठा mlx5_core_dev *mdev, व्योम *in)
अणु
	पूर्णांक sz = MLX5_ST_SZ_BYTES(pbmc_reg);
	व्योम *out;
	पूर्णांक err;

	out = kzalloc(sz, GFP_KERNEL);
	अगर (!out)
		वापस -ENOMEM;

	MLX5_SET(pbmc_reg, in, local_port, 1);
	err = mlx5_core_access_reg(mdev, in, sz, out, sz, MLX5_REG_PBMC, 0, 1);

	kमुक्त(out);
	वापस err;
पूर्ण

/* buffer[i]: buffer that priority i mapped to */
पूर्णांक mlx5e_port_query_priority2buffer(काष्ठा mlx5_core_dev *mdev, u8 *buffer)
अणु
	पूर्णांक sz = MLX5_ST_SZ_BYTES(pptb_reg);
	u32 prio_x_buff;
	व्योम *out;
	व्योम *in;
	पूर्णांक prio;
	पूर्णांक err;

	in = kzalloc(sz, GFP_KERNEL);
	out = kzalloc(sz, GFP_KERNEL);
	अगर (!in || !out) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	MLX5_SET(pptb_reg, in, local_port, 1);
	err = mlx5_core_access_reg(mdev, in, sz, out, sz, MLX5_REG_PPTB, 0, 0);
	अगर (err)
		जाओ out;

	prio_x_buff = MLX5_GET(pptb_reg, out, prio_x_buff);
	क्रम (prio = 0; prio < 8; prio++) अणु
		buffer[prio] = (u8)(prio_x_buff >> (4 * prio)) & 0xF;
		mlx5_core_dbg(mdev, "prio %d, buffer %d\n", prio, buffer[prio]);
	पूर्ण
out:
	kमुक्त(in);
	kमुक्त(out);
	वापस err;
पूर्ण

पूर्णांक mlx5e_port_set_priority2buffer(काष्ठा mlx5_core_dev *mdev, u8 *buffer)
अणु
	पूर्णांक sz = MLX5_ST_SZ_BYTES(pptb_reg);
	u32 prio_x_buff;
	व्योम *out;
	व्योम *in;
	पूर्णांक prio;
	पूर्णांक err;

	in = kzalloc(sz, GFP_KERNEL);
	out = kzalloc(sz, GFP_KERNEL);
	अगर (!in || !out) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	/* First query the pptb रेजिस्टर */
	MLX5_SET(pptb_reg, in, local_port, 1);
	err = mlx5_core_access_reg(mdev, in, sz, out, sz, MLX5_REG_PPTB, 0, 0);
	अगर (err)
		जाओ out;

	स_नकल(in, out, sz);
	MLX5_SET(pptb_reg, in, local_port, 1);

	/* Update the pm and prio_x_buff */
	MLX5_SET(pptb_reg, in, pm, 0xFF);

	prio_x_buff = 0;
	क्रम (prio = 0; prio < 8; prio++)
		prio_x_buff |= (buffer[prio] << (4 * prio));
	MLX5_SET(pptb_reg, in, prio_x_buff, prio_x_buff);

	err = mlx5_core_access_reg(mdev, in, sz, out, sz, MLX5_REG_PPTB, 0, 1);

out:
	kमुक्त(in);
	kमुक्त(out);
	वापस err;
पूर्ण

क्रमागत mlx5e_fec_supported_link_mode अणु
	MLX5E_FEC_SUPPORTED_LINK_MODES_10G_40G,
	MLX5E_FEC_SUPPORTED_LINK_MODES_25G,
	MLX5E_FEC_SUPPORTED_LINK_MODES_50G,
	MLX5E_FEC_SUPPORTED_LINK_MODES_56G,
	MLX5E_FEC_SUPPORTED_LINK_MODES_100G,
	MLX5E_FEC_SUPPORTED_LINK_MODE_50G_1X,
	MLX5E_FEC_SUPPORTED_LINK_MODE_100G_2X,
	MLX5E_FEC_SUPPORTED_LINK_MODE_200G_4X,
	MLX5E_FEC_SUPPORTED_LINK_MODE_400G_8X,
	MLX5E_MAX_FEC_SUPPORTED_LINK_MODE,
पूर्ण;

#घोषणा MLX5E_FEC_FIRST_50G_PER_LANE_MODE MLX5E_FEC_SUPPORTED_LINK_MODE_50G_1X

#घोषणा MLX5E_FEC_OVERRIDE_ADMIN_POLICY(buf, policy, ग_लिखो, link)			\
	करो अणु										\
		u16 *_policy = &(policy);						\
		u32 *_buf = buf;							\
											\
		अगर (ग_लिखो)								\
			MLX5_SET(pplm_reg, _buf, fec_override_admin_##link, *_policy);	\
		अन्यथा									\
			*_policy = MLX5_GET(pplm_reg, _buf, fec_override_admin_##link);	\
	पूर्ण जबतक (0)

/* get/set FEC admin field क्रम a given speed */
अटल पूर्णांक mlx5e_fec_admin_field(u32 *pplm, u16 *fec_policy, bool ग_लिखो,
				 क्रमागत mlx5e_fec_supported_link_mode link_mode)
अणु
	चयन (link_mode) अणु
	हाल MLX5E_FEC_SUPPORTED_LINK_MODES_10G_40G:
		MLX5E_FEC_OVERRIDE_ADMIN_POLICY(pplm, *fec_policy, ग_लिखो, 10g_40g);
		अवरोध;
	हाल MLX5E_FEC_SUPPORTED_LINK_MODES_25G:
		MLX5E_FEC_OVERRIDE_ADMIN_POLICY(pplm, *fec_policy, ग_लिखो, 25g);
		अवरोध;
	हाल MLX5E_FEC_SUPPORTED_LINK_MODES_50G:
		MLX5E_FEC_OVERRIDE_ADMIN_POLICY(pplm, *fec_policy, ग_लिखो, 50g);
		अवरोध;
	हाल MLX5E_FEC_SUPPORTED_LINK_MODES_56G:
		MLX5E_FEC_OVERRIDE_ADMIN_POLICY(pplm, *fec_policy, ग_लिखो, 56g);
		अवरोध;
	हाल MLX5E_FEC_SUPPORTED_LINK_MODES_100G:
		MLX5E_FEC_OVERRIDE_ADMIN_POLICY(pplm, *fec_policy, ग_लिखो, 100g);
		अवरोध;
	हाल MLX5E_FEC_SUPPORTED_LINK_MODE_50G_1X:
		MLX5E_FEC_OVERRIDE_ADMIN_POLICY(pplm, *fec_policy, ग_लिखो, 50g_1x);
		अवरोध;
	हाल MLX5E_FEC_SUPPORTED_LINK_MODE_100G_2X:
		MLX5E_FEC_OVERRIDE_ADMIN_POLICY(pplm, *fec_policy, ग_लिखो, 100g_2x);
		अवरोध;
	हाल MLX5E_FEC_SUPPORTED_LINK_MODE_200G_4X:
		MLX5E_FEC_OVERRIDE_ADMIN_POLICY(pplm, *fec_policy, ग_लिखो, 200g_4x);
		अवरोध;
	हाल MLX5E_FEC_SUPPORTED_LINK_MODE_400G_8X:
		MLX5E_FEC_OVERRIDE_ADMIN_POLICY(pplm, *fec_policy, ग_लिखो, 400g_8x);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा MLX5E_GET_FEC_OVERRIDE_CAP(buf, link)  \
	MLX5_GET(pplm_reg, buf, fec_override_cap_##link)

/* वापसs FEC capabilities क्रम a given speed */
अटल पूर्णांक mlx5e_get_fec_cap_field(u32 *pplm, u16 *fec_cap,
				   क्रमागत mlx5e_fec_supported_link_mode link_mode)
अणु
	चयन (link_mode) अणु
	हाल MLX5E_FEC_SUPPORTED_LINK_MODES_10G_40G:
		*fec_cap = MLX5E_GET_FEC_OVERRIDE_CAP(pplm, 10g_40g);
		अवरोध;
	हाल MLX5E_FEC_SUPPORTED_LINK_MODES_25G:
		*fec_cap = MLX5E_GET_FEC_OVERRIDE_CAP(pplm, 25g);
		अवरोध;
	हाल MLX5E_FEC_SUPPORTED_LINK_MODES_50G:
		*fec_cap = MLX5E_GET_FEC_OVERRIDE_CAP(pplm, 50g);
		अवरोध;
	हाल MLX5E_FEC_SUPPORTED_LINK_MODES_56G:
		*fec_cap = MLX5E_GET_FEC_OVERRIDE_CAP(pplm, 56g);
		अवरोध;
	हाल MLX5E_FEC_SUPPORTED_LINK_MODES_100G:
		*fec_cap = MLX5E_GET_FEC_OVERRIDE_CAP(pplm, 100g);
		अवरोध;
	हाल MLX5E_FEC_SUPPORTED_LINK_MODE_50G_1X:
		*fec_cap = MLX5E_GET_FEC_OVERRIDE_CAP(pplm, 50g_1x);
		अवरोध;
	हाल MLX5E_FEC_SUPPORTED_LINK_MODE_100G_2X:
		*fec_cap = MLX5E_GET_FEC_OVERRIDE_CAP(pplm, 100g_2x);
		अवरोध;
	हाल MLX5E_FEC_SUPPORTED_LINK_MODE_200G_4X:
		*fec_cap = MLX5E_GET_FEC_OVERRIDE_CAP(pplm, 200g_4x);
		अवरोध;
	हाल MLX5E_FEC_SUPPORTED_LINK_MODE_400G_8X:
		*fec_cap = MLX5E_GET_FEC_OVERRIDE_CAP(pplm, 400g_8x);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

bool mlx5e_fec_in_caps(काष्ठा mlx5_core_dev *dev, पूर्णांक fec_policy)
अणु
	bool fec_50g_per_lane = MLX5_CAP_PCAM_FEATURE(dev, fec_50G_per_lane_in_pplm);
	u32 out[MLX5_ST_SZ_DW(pplm_reg)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(pplm_reg)] = अणुपूर्ण;
	पूर्णांक sz = MLX5_ST_SZ_BYTES(pplm_reg);
	पूर्णांक err;
	पूर्णांक i;

	अगर (!MLX5_CAP_GEN(dev, pcam_reg) || !MLX5_CAP_PCAM_REG(dev, pplm))
		वापस false;

	MLX5_SET(pplm_reg, in, local_port, 1);
	err =  mlx5_core_access_reg(dev, in, sz, out, sz, MLX5_REG_PPLM, 0, 0);
	अगर (err)
		वापस false;

	क्रम (i = 0; i < MLX5E_MAX_FEC_SUPPORTED_LINK_MODE; i++) अणु
		u16 fec_caps;

		अगर (i >= MLX5E_FEC_FIRST_50G_PER_LANE_MODE && !fec_50g_per_lane)
			अवरोध;

		mlx5e_get_fec_cap_field(out, &fec_caps, i);
		अगर (fec_caps & fec_policy)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

पूर्णांक mlx5e_get_fec_mode(काष्ठा mlx5_core_dev *dev, u32 *fec_mode_active,
		       u16 *fec_configured_mode)
अणु
	bool fec_50g_per_lane = MLX5_CAP_PCAM_FEATURE(dev, fec_50G_per_lane_in_pplm);
	u32 out[MLX5_ST_SZ_DW(pplm_reg)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(pplm_reg)] = अणुपूर्ण;
	पूर्णांक sz = MLX5_ST_SZ_BYTES(pplm_reg);
	पूर्णांक err;
	पूर्णांक i;

	अगर (!MLX5_CAP_GEN(dev, pcam_reg))
		वापस -EOPNOTSUPP;

	अगर (!MLX5_CAP_PCAM_REG(dev, pplm))
		वापस -EOPNOTSUPP;

	MLX5_SET(pplm_reg, in, local_port, 1);
	err =  mlx5_core_access_reg(dev, in, sz, out, sz, MLX5_REG_PPLM, 0, 0);
	अगर (err)
		वापस err;

	*fec_mode_active = MLX5_GET(pplm_reg, out, fec_mode_active);

	अगर (!fec_configured_mode)
		जाओ out;

	*fec_configured_mode = 0;
	क्रम (i = 0; i < MLX5E_MAX_FEC_SUPPORTED_LINK_MODE; i++) अणु
		अगर (i >= MLX5E_FEC_FIRST_50G_PER_LANE_MODE && !fec_50g_per_lane)
			अवरोध;

		mlx5e_fec_admin_field(out, fec_configured_mode, 0, i);
		अगर (*fec_configured_mode != 0)
			जाओ out;
	पूर्ण
out:
	वापस 0;
पूर्ण

पूर्णांक mlx5e_set_fec_mode(काष्ठा mlx5_core_dev *dev, u16 fec_policy)
अणु
	bool fec_50g_per_lane = MLX5_CAP_PCAM_FEATURE(dev, fec_50G_per_lane_in_pplm);
	u32 out[MLX5_ST_SZ_DW(pplm_reg)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(pplm_reg)] = अणुपूर्ण;
	पूर्णांक sz = MLX5_ST_SZ_BYTES(pplm_reg);
	u16 fec_policy_स्वतः = 0;
	पूर्णांक err;
	पूर्णांक i;

	अगर (!MLX5_CAP_GEN(dev, pcam_reg))
		वापस -EOPNOTSUPP;

	अगर (!MLX5_CAP_PCAM_REG(dev, pplm))
		वापस -EOPNOTSUPP;

	अगर (fec_policy >= (1 << MLX5E_FEC_LLRS_272_257_1) && !fec_50g_per_lane)
		वापस -EOPNOTSUPP;

	अगर (fec_policy && !mlx5e_fec_in_caps(dev, fec_policy))
		वापस -EOPNOTSUPP;

	MLX5_SET(pplm_reg, in, local_port, 1);
	err = mlx5_core_access_reg(dev, in, sz, out, sz, MLX5_REG_PPLM, 0, 0);
	अगर (err)
		वापस err;

	MLX5_SET(pplm_reg, out, local_port, 1);

	क्रम (i = 0; i < MLX5E_MAX_FEC_SUPPORTED_LINK_MODE; i++) अणु
		u16 conf_fec = fec_policy;
		u16 fec_caps = 0;

		अगर (i >= MLX5E_FEC_FIRST_50G_PER_LANE_MODE && !fec_50g_per_lane)
			अवरोध;

		/* RS fec in ethtool is mapped to MLX5E_FEC_RS_528_514
		 * to link modes up to 25G per lane and to
		 * MLX5E_FEC_RS_544_514 in the new link modes based on
		 * 50 G per lane
		 */
		अगर (conf_fec == (1 << MLX5E_FEC_RS_528_514) &&
		    i >= MLX5E_FEC_FIRST_50G_PER_LANE_MODE)
			conf_fec = (1 << MLX5E_FEC_RS_544_514);

		mlx5e_get_fec_cap_field(out, &fec_caps, i);

		/* policy supported क्रम link speed */
		अगर (fec_caps & conf_fec)
			mlx5e_fec_admin_field(out, &conf_fec, 1, i);
		अन्यथा
			/* set FEC to स्वतः*/
			mlx5e_fec_admin_field(out, &fec_policy_स्वतः, 1, i);
	पूर्ण

	वापस mlx5_core_access_reg(dev, out, sz, out, sz, MLX5_REG_PPLM, 0, 1);
पूर्ण
