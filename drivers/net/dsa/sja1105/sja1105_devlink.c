<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2018-2019, Vladimir Oltean <olteanv@gmail.com>
 * Copyright 2020 NXP Semiconductors
 */
#समावेश "sja1105.h"

/* Since devlink regions have a fixed size and the अटल config has a variable
 * size, we need to calculate the maximum possible अटल config size by
 * creating a dummy config with all table entries populated to the max, and get
 * its packed length. This is करोne dynamically as opposed to simply hardcoding
 * a number, since currently not all अटल config tables are implemented, so
 * we are aव्योमing a possible code desynchronization.
 */
अटल माप_प्रकार sja1105_अटल_config_get_max_size(काष्ठा sja1105_निजी *priv)
अणु
	काष्ठा sja1105_अटल_config config;
	क्रमागत sja1105_blk_idx blk_idx;
	पूर्णांक rc;

	rc = sja1105_अटल_config_init(&config,
					priv->info->अटल_ops,
					priv->info->device_id);
	अगर (rc)
		वापस 0;

	क्रम (blk_idx = 0; blk_idx < BLK_IDX_MAX; blk_idx++) अणु
		काष्ठा sja1105_table *table = &config.tables[blk_idx];

		table->entry_count = table->ops->max_entry_count;
	पूर्ण

	वापस sja1105_अटल_config_get_length(&config);
पूर्ण

अटल पूर्णांक
sja1105_region_अटल_config_snapshot(काष्ठा devlink *dl,
				      स्थिर काष्ठा devlink_region_ops *ops,
				      काष्ठा netlink_ext_ack *extack,
				      u8 **data)
अणु
	काष्ठा dsa_चयन *ds = dsa_devlink_to_ds(dl);
	काष्ठा sja1105_निजी *priv = ds->priv;
	माप_प्रकार max_len, len;

	len = sja1105_अटल_config_get_length(&priv->अटल_config);
	max_len = sja1105_अटल_config_get_max_size(priv);

	*data = kसुस्मृति(max_len, माप(u8), GFP_KERNEL);
	अगर (!*data)
		वापस -ENOMEM;

	वापस अटल_config_buf_prepare_क्रम_upload(priv, *data, len);
पूर्ण

अटल काष्ठा devlink_region_ops sja1105_region_अटल_config_ops = अणु
	.name = "static-config",
	.snapshot = sja1105_region_अटल_config_snapshot,
	.deकाष्ठाor = kमुक्त,
पूर्ण;

क्रमागत sja1105_region_id अणु
	SJA1105_REGION_STATIC_CONFIG = 0,
पूर्ण;

काष्ठा sja1105_region अणु
	स्थिर काष्ठा devlink_region_ops *ops;
	माप_प्रकार (*get_size)(काष्ठा sja1105_निजी *priv);
पूर्ण;

अटल काष्ठा sja1105_region sja1105_regions[] = अणु
	[SJA1105_REGION_STATIC_CONFIG] = अणु
		.ops = &sja1105_region_अटल_config_ops,
		.get_size = sja1105_अटल_config_get_max_size,
	पूर्ण,
पूर्ण;

अटल पूर्णांक sja1105_setup_devlink_regions(काष्ठा dsa_चयन *ds)
अणु
	पूर्णांक i, num_regions = ARRAY_SIZE(sja1105_regions);
	काष्ठा sja1105_निजी *priv = ds->priv;
	स्थिर काष्ठा devlink_region_ops *ops;
	काष्ठा devlink_region *region;
	u64 size;

	priv->regions = kसुस्मृति(num_regions, माप(काष्ठा devlink_region *),
				GFP_KERNEL);
	अगर (!priv->regions)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_regions; i++) अणु
		size = sja1105_regions[i].get_size(priv);
		ops = sja1105_regions[i].ops;

		region = dsa_devlink_region_create(ds, ops, 1, size);
		अगर (IS_ERR(region)) अणु
			जबतक (i-- >= 0)
				dsa_devlink_region_destroy(priv->regions[i]);
			वापस PTR_ERR(region);
		पूर्ण

		priv->regions[i] = region;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sja1105_tearकरोwn_devlink_regions(काष्ठा dsa_चयन *ds)
अणु
	पूर्णांक i, num_regions = ARRAY_SIZE(sja1105_regions);
	काष्ठा sja1105_निजी *priv = ds->priv;

	क्रम (i = 0; i < num_regions; i++)
		dsa_devlink_region_destroy(priv->regions[i]);

	kमुक्त(priv->regions);
पूर्ण

अटल पूर्णांक sja1105_best_efक्रमt_vlan_filtering_get(काष्ठा sja1105_निजी *priv,
						  bool *be_vlan)
अणु
	*be_vlan = priv->best_efक्रमt_vlan_filtering;

	वापस 0;
पूर्ण

अटल पूर्णांक sja1105_best_efक्रमt_vlan_filtering_set(काष्ठा sja1105_निजी *priv,
						  bool be_vlan)
अणु
	काष्ठा dsa_चयन *ds = priv->ds;
	bool vlan_filtering;
	पूर्णांक port;
	पूर्णांक rc;

	priv->best_efक्रमt_vlan_filtering = be_vlan;

	rtnl_lock();
	क्रम (port = 0; port < ds->num_ports; port++) अणु
		काष्ठा dsa_port *dp;

		अगर (!dsa_is_user_port(ds, port))
			जारी;

		dp = dsa_to_port(ds, port);
		vlan_filtering = dsa_port_is_vlan_filtering(dp);

		rc = sja1105_vlan_filtering(ds, port, vlan_filtering, शून्य);
		अगर (rc)
			अवरोध;
	पूर्ण
	rtnl_unlock();

	वापस rc;
पूर्ण

क्रमागत sja1105_devlink_param_id अणु
	SJA1105_DEVLINK_PARAM_ID_BASE = DEVLINK_PARAM_GENERIC_ID_MAX,
	SJA1105_DEVLINK_PARAM_ID_BEST_EFFORT_VLAN_FILTERING,
पूर्ण;

पूर्णांक sja1105_devlink_param_get(काष्ठा dsa_चयन *ds, u32 id,
			      काष्ठा devlink_param_gset_ctx *ctx)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	पूर्णांक err;

	चयन (id) अणु
	हाल SJA1105_DEVLINK_PARAM_ID_BEST_EFFORT_VLAN_FILTERING:
		err = sja1105_best_efक्रमt_vlan_filtering_get(priv,
							     &ctx->val.vbool);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक sja1105_devlink_param_set(काष्ठा dsa_चयन *ds, u32 id,
			      काष्ठा devlink_param_gset_ctx *ctx)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	पूर्णांक err;

	चयन (id) अणु
	हाल SJA1105_DEVLINK_PARAM_ID_BEST_EFFORT_VLAN_FILTERING:
		err = sja1105_best_efक्रमt_vlan_filtering_set(priv,
							     ctx->val.vbool);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा devlink_param sja1105_devlink_params[] = अणु
	DSA_DEVLINK_PARAM_DRIVER(SJA1105_DEVLINK_PARAM_ID_BEST_EFFORT_VLAN_FILTERING,
				 "best_effort_vlan_filtering",
				 DEVLINK_PARAM_TYPE_BOOL,
				 BIT(DEVLINK_PARAM_CMODE_RUNTIME)),
पूर्ण;

अटल पूर्णांक sja1105_setup_devlink_params(काष्ठा dsa_चयन *ds)
अणु
	वापस dsa_devlink_params_रेजिस्टर(ds, sja1105_devlink_params,
					   ARRAY_SIZE(sja1105_devlink_params));
पूर्ण

अटल व्योम sja1105_tearकरोwn_devlink_params(काष्ठा dsa_चयन *ds)
अणु
	dsa_devlink_params_unरेजिस्टर(ds, sja1105_devlink_params,
				      ARRAY_SIZE(sja1105_devlink_params));
पूर्ण

पूर्णांक sja1105_devlink_info_get(काष्ठा dsa_चयन *ds,
			     काष्ठा devlink_info_req *req,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	पूर्णांक rc;

	rc = devlink_info_driver_name_put(req, "sja1105");
	अगर (rc)
		वापस rc;

	rc = devlink_info_version_fixed_put(req,
					    DEVLINK_INFO_VERSION_GENERIC_ASIC_ID,
					    priv->info->name);
	वापस rc;
पूर्ण

पूर्णांक sja1105_devlink_setup(काष्ठा dsa_चयन *ds)
अणु
	पूर्णांक rc;

	rc = sja1105_setup_devlink_params(ds);
	अगर (rc)
		वापस rc;

	rc = sja1105_setup_devlink_regions(ds);
	अगर (rc < 0) अणु
		sja1105_tearकरोwn_devlink_params(ds);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

व्योम sja1105_devlink_tearकरोwn(काष्ठा dsa_चयन *ds)
अणु
	sja1105_tearकरोwn_devlink_params(ds);
	sja1105_tearकरोwn_devlink_regions(ds);
पूर्ण
