<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
#समावेश <net/dsa.h>

#समावेश "chip.h"
#समावेश "devlink.h"
#समावेश "global1.h"
#समावेश "global2.h"
#समावेश "port.h"

अटल पूर्णांक mv88e6xxx_atu_get_hash(काष्ठा mv88e6xxx_chip *chip, u8 *hash)
अणु
	अगर (chip->info->ops->atu_get_hash)
		वापस chip->info->ops->atu_get_hash(chip, hash);

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक mv88e6xxx_atu_set_hash(काष्ठा mv88e6xxx_chip *chip, u8 hash)
अणु
	अगर (chip->info->ops->atu_set_hash)
		वापस chip->info->ops->atu_set_hash(chip, hash);

	वापस -EOPNOTSUPP;
पूर्ण

क्रमागत mv88e6xxx_devlink_param_id अणु
	MV88E6XXX_DEVLINK_PARAM_ID_BASE = DEVLINK_PARAM_GENERIC_ID_MAX,
	MV88E6XXX_DEVLINK_PARAM_ID_ATU_HASH,
पूर्ण;

पूर्णांक mv88e6xxx_devlink_param_get(काष्ठा dsa_चयन *ds, u32 id,
				काष्ठा devlink_param_gset_ctx *ctx)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक err;

	mv88e6xxx_reg_lock(chip);

	चयन (id) अणु
	हाल MV88E6XXX_DEVLINK_PARAM_ID_ATU_HASH:
		err = mv88e6xxx_atu_get_hash(chip, &ctx->val.vu8);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	mv88e6xxx_reg_unlock(chip);

	वापस err;
पूर्ण

पूर्णांक mv88e6xxx_devlink_param_set(काष्ठा dsa_चयन *ds, u32 id,
				काष्ठा devlink_param_gset_ctx *ctx)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक err;

	mv88e6xxx_reg_lock(chip);

	चयन (id) अणु
	हाल MV88E6XXX_DEVLINK_PARAM_ID_ATU_HASH:
		err = mv88e6xxx_atu_set_hash(chip, ctx->val.vu8);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	mv88e6xxx_reg_unlock(chip);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा devlink_param mv88e6xxx_devlink_params[] = अणु
	DSA_DEVLINK_PARAM_DRIVER(MV88E6XXX_DEVLINK_PARAM_ID_ATU_HASH,
				 "ATU_hash", DEVLINK_PARAM_TYPE_U8,
				 BIT(DEVLINK_PARAM_CMODE_RUNTIME)),
पूर्ण;

पूर्णांक mv88e6xxx_setup_devlink_params(काष्ठा dsa_चयन *ds)
अणु
	वापस dsa_devlink_params_रेजिस्टर(ds, mv88e6xxx_devlink_params,
					   ARRAY_SIZE(mv88e6xxx_devlink_params));
पूर्ण

व्योम mv88e6xxx_tearकरोwn_devlink_params(काष्ठा dsa_चयन *ds)
अणु
	dsa_devlink_params_unरेजिस्टर(ds, mv88e6xxx_devlink_params,
				      ARRAY_SIZE(mv88e6xxx_devlink_params));
पूर्ण

क्रमागत mv88e6xxx_devlink_resource_id अणु
	MV88E6XXX_RESOURCE_ID_ATU,
	MV88E6XXX_RESOURCE_ID_ATU_BIN_0,
	MV88E6XXX_RESOURCE_ID_ATU_BIN_1,
	MV88E6XXX_RESOURCE_ID_ATU_BIN_2,
	MV88E6XXX_RESOURCE_ID_ATU_BIN_3,
पूर्ण;

अटल u64 mv88e6xxx_devlink_atu_bin_get(काष्ठा mv88e6xxx_chip *chip,
					 u16 bin)
अणु
	u16 occupancy = 0;
	पूर्णांक err;

	mv88e6xxx_reg_lock(chip);

	err = mv88e6xxx_g2_atu_stats_set(chip, MV88E6XXX_G2_ATU_STATS_MODE_ALL,
					 bin);
	अगर (err) अणु
		dev_err(chip->dev, "failed to set ATU stats kind/bin\n");
		जाओ unlock;
	पूर्ण

	err = mv88e6xxx_g1_atu_get_next(chip, 0);
	अगर (err) अणु
		dev_err(chip->dev, "failed to perform ATU get next\n");
		जाओ unlock;
	पूर्ण

	err = mv88e6xxx_g2_atu_stats_get(chip, &occupancy);
	अगर (err) अणु
		dev_err(chip->dev, "failed to get ATU stats\n");
		जाओ unlock;
	पूर्ण

	occupancy &= MV88E6XXX_G2_ATU_STATS_MASK;

unlock:
	mv88e6xxx_reg_unlock(chip);

	वापस occupancy;
पूर्ण

अटल u64 mv88e6xxx_devlink_atu_bin_0_get(व्योम *priv)
अणु
	काष्ठा mv88e6xxx_chip *chip = priv;

	वापस mv88e6xxx_devlink_atu_bin_get(chip,
					     MV88E6XXX_G2_ATU_STATS_BIN_0);
पूर्ण

अटल u64 mv88e6xxx_devlink_atu_bin_1_get(व्योम *priv)
अणु
	काष्ठा mv88e6xxx_chip *chip = priv;

	वापस mv88e6xxx_devlink_atu_bin_get(chip,
					     MV88E6XXX_G2_ATU_STATS_BIN_1);
पूर्ण

अटल u64 mv88e6xxx_devlink_atu_bin_2_get(व्योम *priv)
अणु
	काष्ठा mv88e6xxx_chip *chip = priv;

	वापस mv88e6xxx_devlink_atu_bin_get(chip,
					     MV88E6XXX_G2_ATU_STATS_BIN_2);
पूर्ण

अटल u64 mv88e6xxx_devlink_atu_bin_3_get(व्योम *priv)
अणु
	काष्ठा mv88e6xxx_chip *chip = priv;

	वापस mv88e6xxx_devlink_atu_bin_get(chip,
					     MV88E6XXX_G2_ATU_STATS_BIN_3);
पूर्ण

अटल u64 mv88e6xxx_devlink_atu_get(व्योम *priv)
अणु
	वापस mv88e6xxx_devlink_atu_bin_0_get(priv) +
		mv88e6xxx_devlink_atu_bin_1_get(priv) +
		mv88e6xxx_devlink_atu_bin_2_get(priv) +
		mv88e6xxx_devlink_atu_bin_3_get(priv);
पूर्ण

पूर्णांक mv88e6xxx_setup_devlink_resources(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा devlink_resource_size_params size_params;
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक err;

	devlink_resource_size_params_init(&size_params,
					  mv88e6xxx_num_macs(chip),
					  mv88e6xxx_num_macs(chip),
					  1, DEVLINK_RESOURCE_UNIT_ENTRY);

	err = dsa_devlink_resource_रेजिस्टर(ds, "ATU",
					    mv88e6xxx_num_macs(chip),
					    MV88E6XXX_RESOURCE_ID_ATU,
					    DEVLINK_RESOURCE_ID_PARENT_TOP,
					    &size_params);
	अगर (err)
		जाओ out;

	devlink_resource_size_params_init(&size_params,
					  mv88e6xxx_num_macs(chip) / 4,
					  mv88e6xxx_num_macs(chip) / 4,
					  1, DEVLINK_RESOURCE_UNIT_ENTRY);

	err = dsa_devlink_resource_रेजिस्टर(ds, "ATU_bin_0",
					    mv88e6xxx_num_macs(chip) / 4,
					    MV88E6XXX_RESOURCE_ID_ATU_BIN_0,
					    MV88E6XXX_RESOURCE_ID_ATU,
					    &size_params);
	अगर (err)
		जाओ out;

	err = dsa_devlink_resource_रेजिस्टर(ds, "ATU_bin_1",
					    mv88e6xxx_num_macs(chip) / 4,
					    MV88E6XXX_RESOURCE_ID_ATU_BIN_1,
					    MV88E6XXX_RESOURCE_ID_ATU,
					    &size_params);
	अगर (err)
		जाओ out;

	err = dsa_devlink_resource_रेजिस्टर(ds, "ATU_bin_2",
					    mv88e6xxx_num_macs(chip) / 4,
					    MV88E6XXX_RESOURCE_ID_ATU_BIN_2,
					    MV88E6XXX_RESOURCE_ID_ATU,
					    &size_params);
	अगर (err)
		जाओ out;

	err = dsa_devlink_resource_रेजिस्टर(ds, "ATU_bin_3",
					    mv88e6xxx_num_macs(chip) / 4,
					    MV88E6XXX_RESOURCE_ID_ATU_BIN_3,
					    MV88E6XXX_RESOURCE_ID_ATU,
					    &size_params);
	अगर (err)
		जाओ out;

	dsa_devlink_resource_occ_get_रेजिस्टर(ds,
					      MV88E6XXX_RESOURCE_ID_ATU,
					      mv88e6xxx_devlink_atu_get,
					      chip);

	dsa_devlink_resource_occ_get_रेजिस्टर(ds,
					      MV88E6XXX_RESOURCE_ID_ATU_BIN_0,
					      mv88e6xxx_devlink_atu_bin_0_get,
					      chip);

	dsa_devlink_resource_occ_get_रेजिस्टर(ds,
					      MV88E6XXX_RESOURCE_ID_ATU_BIN_1,
					      mv88e6xxx_devlink_atu_bin_1_get,
					      chip);

	dsa_devlink_resource_occ_get_रेजिस्टर(ds,
					      MV88E6XXX_RESOURCE_ID_ATU_BIN_2,
					      mv88e6xxx_devlink_atu_bin_2_get,
					      chip);

	dsa_devlink_resource_occ_get_रेजिस्टर(ds,
					      MV88E6XXX_RESOURCE_ID_ATU_BIN_3,
					      mv88e6xxx_devlink_atu_bin_3_get,
					      chip);

	वापस 0;

out:
	dsa_devlink_resources_unरेजिस्टर(ds);
	वापस err;
पूर्ण

अटल पूर्णांक mv88e6xxx_region_global_snapshot(काष्ठा devlink *dl,
					    स्थिर काष्ठा devlink_region_ops *ops,
					    काष्ठा netlink_ext_ack *extack,
					    u8 **data)
अणु
	काष्ठा mv88e6xxx_region_priv *region_priv = ops->priv;
	काष्ठा dsa_चयन *ds = dsa_devlink_to_ds(dl);
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	u16 *रेजिस्टरs;
	पूर्णांक i, err;

	रेजिस्टरs = kदो_स्मृति_array(32, माप(u16), GFP_KERNEL);
	अगर (!रेजिस्टरs)
		वापस -ENOMEM;

	mv88e6xxx_reg_lock(chip);
	क्रम (i = 0; i < 32; i++) अणु
		चयन (region_priv->id) अणु
		हाल MV88E6XXX_REGION_GLOBAL1:
			err = mv88e6xxx_g1_पढ़ो(chip, i, &रेजिस्टरs[i]);
			अवरोध;
		हाल MV88E6XXX_REGION_GLOBAL2:
			err = mv88e6xxx_g2_पढ़ो(chip, i, &रेजिस्टरs[i]);
			अवरोध;
		शेष:
			err = -EOPNOTSUPP;
		पूर्ण

		अगर (err) अणु
			kमुक्त(रेजिस्टरs);
			जाओ out;
		पूर्ण
	पूर्ण
	*data = (u8 *)रेजिस्टरs;
out:
	mv88e6xxx_reg_unlock(chip);

	वापस err;
पूर्ण

/* The ATU entry varies between mv88e6xxx chipset generations. Define
 * a generic क्रमmat which covers all the current and hopefully future
 * mv88e6xxx generations
 */

काष्ठा mv88e6xxx_devlink_atu_entry अणु
	/* The FID is scattered over multiple रेजिस्टरs. */
	u16 fid;
	u16 atu_op;
	u16 atu_data;
	u16 atu_01;
	u16 atu_23;
	u16 atu_45;
पूर्ण;

अटल पूर्णांक mv88e6xxx_region_atu_snapshot_fid(काष्ठा mv88e6xxx_chip *chip,
					     पूर्णांक fid,
					     काष्ठा mv88e6xxx_devlink_atu_entry *table,
					     पूर्णांक *count)
अणु
	u16 atu_op, atu_data, atu_01, atu_23, atu_45;
	काष्ठा mv88e6xxx_atu_entry addr;
	पूर्णांक err;

	addr.state = 0;
	eth_broadcast_addr(addr.mac);

	करो अणु
		err = mv88e6xxx_g1_atu_getnext(chip, fid, &addr);
		अगर (err)
			वापस err;

		अगर (!addr.state)
			अवरोध;

		err = mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_ATU_OP, &atu_op);
		अगर (err)
			वापस err;

		err = mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_ATU_DATA, &atu_data);
		अगर (err)
			वापस err;

		err = mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_ATU_MAC01, &atu_01);
		अगर (err)
			वापस err;

		err = mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_ATU_MAC23, &atu_23);
		अगर (err)
			वापस err;

		err = mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_ATU_MAC45, &atu_45);
		अगर (err)
			वापस err;

		table[*count].fid = fid;
		table[*count].atu_op = atu_op;
		table[*count].atu_data = atu_data;
		table[*count].atu_01 = atu_01;
		table[*count].atu_23 = atu_23;
		table[*count].atu_45 = atu_45;
		(*count)++;
	पूर्ण जबतक (!is_broadcast_ether_addr(addr.mac));

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_region_atu_snapshot(काष्ठा devlink *dl,
					 स्थिर काष्ठा devlink_region_ops *ops,
					 काष्ठा netlink_ext_ack *extack,
					 u8 **data)
अणु
	काष्ठा dsa_चयन *ds = dsa_devlink_to_ds(dl);
	DECLARE_BITMAP(fid_biपंचांगap, MV88E6XXX_N_FID);
	काष्ठा mv88e6xxx_devlink_atu_entry *table;
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक fid = -1, count, err;

	table = kदो_स्मृति_array(mv88e6xxx_num_databases(chip),
			      माप(काष्ठा mv88e6xxx_devlink_atu_entry),
			      GFP_KERNEL);
	अगर (!table)
		वापस -ENOMEM;

	स_रखो(table, 0, mv88e6xxx_num_databases(chip) *
	       माप(काष्ठा mv88e6xxx_devlink_atu_entry));

	count = 0;

	mv88e6xxx_reg_lock(chip);

	err = mv88e6xxx_fid_map(chip, fid_biपंचांगap);
	अगर (err) अणु
		kमुक्त(table);
		जाओ out;
	पूर्ण

	जबतक (1) अणु
		fid = find_next_bit(fid_biपंचांगap, MV88E6XXX_N_FID, fid + 1);
		अगर (fid == MV88E6XXX_N_FID)
			अवरोध;

		err =  mv88e6xxx_region_atu_snapshot_fid(chip, fid, table,
							 &count);
		अगर (err) अणु
			kमुक्त(table);
			जाओ out;
		पूर्ण
	पूर्ण
	*data = (u8 *)table;
out:
	mv88e6xxx_reg_unlock(chip);

	वापस err;
पूर्ण

/**
 * काष्ठा mv88e6xxx_devlink_vtu_entry - Devlink VTU entry
 * @fid:   Global1/2:   FID and VLAN policy.
 * @sid:   Global1/3:   SID, unknown filters and learning.
 * @op:    Global1/5:   FID (old chipsets).
 * @vid:   Global1/6:   VID, valid, and page.
 * @data:  Global1/7-9: Membership data and priority override.
 * @resvd: Reserved. Also happens to align the size to 16B.
 *
 * The VTU entry क्रमmat varies between chipset generations, the
 * descriptions above represent the superset of all possible
 * inक्रमmation, not all fields are valid on all devices. Since this is
 * a low-level debug पूर्णांकerface, copy all data verbatim and defer
 * parsing to the consumer.
 */
काष्ठा mv88e6xxx_devlink_vtu_entry अणु
	u16 fid;
	u16 sid;
	u16 op;
	u16 vid;
	u16 data[3];
	u16 resvd;
पूर्ण;

अटल पूर्णांक mv88e6xxx_region_vtu_snapshot(काष्ठा devlink *dl,
					 स्थिर काष्ठा devlink_region_ops *ops,
					 काष्ठा netlink_ext_ack *extack,
					 u8 **data)
अणु
	काष्ठा mv88e6xxx_devlink_vtu_entry *table, *entry;
	काष्ठा dsa_चयन *ds = dsa_devlink_to_ds(dl);
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	काष्ठा mv88e6xxx_vtu_entry vlan;
	पूर्णांक err;

	table = kसुस्मृति(mv88e6xxx_max_vid(chip) + 1,
			माप(काष्ठा mv88e6xxx_devlink_vtu_entry),
			GFP_KERNEL);
	अगर (!table)
		वापस -ENOMEM;

	entry = table;
	vlan.vid = mv88e6xxx_max_vid(chip);
	vlan.valid = false;

	mv88e6xxx_reg_lock(chip);

	करो अणु
		err = mv88e6xxx_g1_vtu_getnext(chip, &vlan);
		अगर (err)
			अवरोध;

		अगर (!vlan.valid)
			अवरोध;

		err = err ? : mv88e6xxx_g1_पढ़ो(chip, MV88E6352_G1_VTU_FID,
						&entry->fid);
		err = err ? : mv88e6xxx_g1_पढ़ो(chip, MV88E6352_G1_VTU_SID,
						&entry->sid);
		err = err ? : mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_VTU_OP,
						&entry->op);
		err = err ? : mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_VTU_VID,
						&entry->vid);
		err = err ? : mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_VTU_DATA1,
						&entry->data[0]);
		err = err ? : mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_VTU_DATA2,
						&entry->data[1]);
		err = err ? : mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_VTU_DATA3,
						&entry->data[2]);
		अगर (err)
			अवरोध;

		entry++;
	पूर्ण जबतक (vlan.vid < mv88e6xxx_max_vid(chip));

	mv88e6xxx_reg_unlock(chip);

	अगर (err) अणु
		kमुक्त(table);
		वापस err;
	पूर्ण

	*data = (u8 *)table;
	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_region_pvt_snapshot(काष्ठा devlink *dl,
					 स्थिर काष्ठा devlink_region_ops *ops,
					 काष्ठा netlink_ext_ack *extack,
					 u8 **data)
अणु
	काष्ठा dsa_चयन *ds = dsa_devlink_to_ds(dl);
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक dev, port, err;
	u16 *pvt, *cur;

	pvt = kसुस्मृति(MV88E6XXX_MAX_PVT_ENTRIES, माप(*pvt), GFP_KERNEL);
	अगर (!pvt)
		वापस -ENOMEM;

	mv88e6xxx_reg_lock(chip);

	cur = pvt;
	क्रम (dev = 0; dev < MV88E6XXX_MAX_PVT_SWITCHES; dev++) अणु
		क्रम (port = 0; port < MV88E6XXX_MAX_PVT_PORTS; port++) अणु
			err = mv88e6xxx_g2_pvt_पढ़ो(chip, dev, port, cur);
			अगर (err)
				अवरोध;

			cur++;
		पूर्ण
	पूर्ण

	mv88e6xxx_reg_unlock(chip);

	अगर (err) अणु
		kमुक्त(pvt);
		वापस err;
	पूर्ण

	*data = (u8 *)pvt;
	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_region_port_snapshot(काष्ठा devlink_port *devlink_port,
					  स्थिर काष्ठा devlink_port_region_ops *ops,
					  काष्ठा netlink_ext_ack *extack,
					  u8 **data)
अणु
	काष्ठा dsa_चयन *ds = dsa_devlink_port_to_ds(devlink_port);
	पूर्णांक port = dsa_devlink_port_to_port(devlink_port);
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	u16 *रेजिस्टरs;
	पूर्णांक i, err;

	रेजिस्टरs = kदो_स्मृति_array(32, माप(u16), GFP_KERNEL);
	अगर (!रेजिस्टरs)
		वापस -ENOMEM;

	mv88e6xxx_reg_lock(chip);
	क्रम (i = 0; i < 32; i++) अणु
		err = mv88e6xxx_port_पढ़ो(chip, port, i, &रेजिस्टरs[i]);
		अगर (err) अणु
			kमुक्त(रेजिस्टरs);
			जाओ out;
		पूर्ण
	पूर्ण
	*data = (u8 *)रेजिस्टरs;
out:
	mv88e6xxx_reg_unlock(chip);

	वापस err;
पूर्ण

अटल काष्ठा mv88e6xxx_region_priv mv88e6xxx_region_global1_priv = अणु
	.id = MV88E6XXX_REGION_GLOBAL1,
पूर्ण;

अटल काष्ठा devlink_region_ops mv88e6xxx_region_global1_ops = अणु
	.name = "global1",
	.snapshot = mv88e6xxx_region_global_snapshot,
	.deकाष्ठाor = kमुक्त,
	.priv = &mv88e6xxx_region_global1_priv,
पूर्ण;

अटल काष्ठा mv88e6xxx_region_priv mv88e6xxx_region_global2_priv = अणु
	.id = MV88E6XXX_REGION_GLOBAL2,
पूर्ण;

अटल काष्ठा devlink_region_ops mv88e6xxx_region_global2_ops = अणु
	.name = "global2",
	.snapshot = mv88e6xxx_region_global_snapshot,
	.deकाष्ठाor = kमुक्त,
	.priv = &mv88e6xxx_region_global2_priv,
पूर्ण;

अटल काष्ठा devlink_region_ops mv88e6xxx_region_atu_ops = अणु
	.name = "atu",
	.snapshot = mv88e6xxx_region_atu_snapshot,
	.deकाष्ठाor = kमुक्त,
पूर्ण;

अटल काष्ठा devlink_region_ops mv88e6xxx_region_vtu_ops = अणु
	.name = "vtu",
	.snapshot = mv88e6xxx_region_vtu_snapshot,
	.deकाष्ठाor = kमुक्त,
पूर्ण;

अटल काष्ठा devlink_region_ops mv88e6xxx_region_pvt_ops = अणु
	.name = "pvt",
	.snapshot = mv88e6xxx_region_pvt_snapshot,
	.deकाष्ठाor = kमुक्त,
पूर्ण;

अटल स्थिर काष्ठा devlink_port_region_ops mv88e6xxx_region_port_ops = अणु
	.name = "port",
	.snapshot = mv88e6xxx_region_port_snapshot,
	.deकाष्ठाor = kमुक्त,
पूर्ण;

काष्ठा mv88e6xxx_region अणु
	काष्ठा devlink_region_ops *ops;
	u64 size;

	bool (*cond)(काष्ठा mv88e6xxx_chip *chip);
पूर्ण;

अटल काष्ठा mv88e6xxx_region mv88e6xxx_regions[] = अणु
	[MV88E6XXX_REGION_GLOBAL1] = अणु
		.ops = &mv88e6xxx_region_global1_ops,
		.size = 32 * माप(u16)
	पूर्ण,
	[MV88E6XXX_REGION_GLOBAL2] = अणु
		.ops = &mv88e6xxx_region_global2_ops,
		.size = 32 * माप(u16) पूर्ण,
	[MV88E6XXX_REGION_ATU] = अणु
		.ops = &mv88e6xxx_region_atu_ops
	  /* calculated at runसमय */
	पूर्ण,
	[MV88E6XXX_REGION_VTU] = अणु
		.ops = &mv88e6xxx_region_vtu_ops
	  /* calculated at runसमय */
	पूर्ण,
	[MV88E6XXX_REGION_PVT] = अणु
		.ops = &mv88e6xxx_region_pvt_ops,
		.size = MV88E6XXX_MAX_PVT_ENTRIES * माप(u16),
		.cond = mv88e6xxx_has_pvt,
	पूर्ण,
पूर्ण;

अटल व्योम
mv88e6xxx_tearकरोwn_devlink_regions_global(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mv88e6xxx_regions); i++)
		dsa_devlink_region_destroy(chip->regions[i]);
पूर्ण

अटल व्योम
mv88e6xxx_tearकरोwn_devlink_regions_port(काष्ठा mv88e6xxx_chip *chip,
					पूर्णांक port)
अणु
	dsa_devlink_region_destroy(chip->ports[port].region);
पूर्ण

अटल पूर्णांक mv88e6xxx_setup_devlink_regions_port(काष्ठा dsa_चयन *ds,
						काष्ठा mv88e6xxx_chip *chip,
						पूर्णांक port)
अणु
	काष्ठा devlink_region *region;

	region = dsa_devlink_port_region_create(ds,
						port,
						&mv88e6xxx_region_port_ops, 1,
						32 * माप(u16));
	अगर (IS_ERR(region))
		वापस PTR_ERR(region);

	chip->ports[port].region = region;

	वापस 0;
पूर्ण

अटल व्योम
mv88e6xxx_tearकरोwn_devlink_regions_ports(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक port;

	क्रम (port = 0; port < mv88e6xxx_num_ports(chip); port++)
		mv88e6xxx_tearकरोwn_devlink_regions_port(chip, port);
पूर्ण

अटल पूर्णांक mv88e6xxx_setup_devlink_regions_ports(काष्ठा dsa_चयन *ds,
						 काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक port;
	पूर्णांक err;

	क्रम (port = 0; port < mv88e6xxx_num_ports(chip); port++) अणु
		err = mv88e6xxx_setup_devlink_regions_port(ds, chip, port);
		अगर (err)
			जाओ out;
	पूर्ण

	वापस 0;

out:
	जबतक (port-- > 0)
		mv88e6xxx_tearकरोwn_devlink_regions_port(chip, port);

	वापस err;
पूर्ण

अटल पूर्णांक mv88e6xxx_setup_devlink_regions_global(काष्ठा dsa_चयन *ds,
						  काष्ठा mv88e6xxx_chip *chip)
अणु
	bool (*cond)(काष्ठा mv88e6xxx_chip *chip);
	काष्ठा devlink_region_ops *ops;
	काष्ठा devlink_region *region;
	u64 size;
	पूर्णांक i, j;

	क्रम (i = 0; i < ARRAY_SIZE(mv88e6xxx_regions); i++) अणु
		ops = mv88e6xxx_regions[i].ops;
		size = mv88e6xxx_regions[i].size;
		cond = mv88e6xxx_regions[i].cond;

		अगर (cond && !cond(chip))
			जारी;

		चयन (i) अणु
		हाल MV88E6XXX_REGION_ATU:
			size = mv88e6xxx_num_databases(chip) *
				माप(काष्ठा mv88e6xxx_devlink_atu_entry);
			अवरोध;
		हाल MV88E6XXX_REGION_VTU:
			size = (mv88e6xxx_max_vid(chip) + 1) *
				माप(काष्ठा mv88e6xxx_devlink_vtu_entry);
			अवरोध;
		पूर्ण

		region = dsa_devlink_region_create(ds, ops, 1, size);
		अगर (IS_ERR(region))
			जाओ out;
		chip->regions[i] = region;
	पूर्ण
	वापस 0;

out:
	क्रम (j = 0; j < i; j++)
		dsa_devlink_region_destroy(chip->regions[j]);

	वापस PTR_ERR(region);
पूर्ण

पूर्णांक mv88e6xxx_setup_devlink_regions(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक err;

	err = mv88e6xxx_setup_devlink_regions_global(ds, chip);
	अगर (err)
		वापस err;

	err = mv88e6xxx_setup_devlink_regions_ports(ds, chip);
	अगर (err)
		mv88e6xxx_tearकरोwn_devlink_regions_global(chip);

	वापस err;
पूर्ण

व्योम mv88e6xxx_tearकरोwn_devlink_regions(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;

	mv88e6xxx_tearकरोwn_devlink_regions_ports(chip);
	mv88e6xxx_tearकरोwn_devlink_regions_global(chip);
पूर्ण

पूर्णांक mv88e6xxx_devlink_info_get(काष्ठा dsa_चयन *ds,
			       काष्ठा devlink_info_req *req,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक err;

	err = devlink_info_driver_name_put(req, "mv88e6xxx");
	अगर (err)
		वापस err;

	वापस devlink_info_version_fixed_put(req,
					      DEVLINK_INFO_VERSION_GENERIC_ASIC_ID,
					      chip->info->name);
पूर्ण
