<शैली गुरु>
/* Broadcom NetXtreme-C/E network driver.
 *
 * Copyright (c) 2017 Broadcom Limited
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#अगर_अघोषित BNXT_DEVLINK_H
#घोषणा BNXT_DEVLINK_H

/* Struct to hold housekeeping info needed by devlink पूर्णांकerface */
काष्ठा bnxt_dl अणु
	काष्ठा bnxt *bp;	/* back ptr to the controlling dev */
पूर्ण;

अटल अंतरभूत काष्ठा bnxt *bnxt_get_bp_from_dl(काष्ठा devlink *dl)
अणु
	वापस ((काष्ठा bnxt_dl *)devlink_priv(dl))->bp;
पूर्ण

/* To clear devlink poपूर्णांकer from bp, pass शून्य dl */
अटल अंतरभूत व्योम bnxt_link_bp_to_dl(काष्ठा bnxt *bp, काष्ठा devlink *dl)
अणु
	bp->dl = dl;

	/* add a back poपूर्णांकer in dl to bp */
	अगर (dl) अणु
		काष्ठा bnxt_dl *bp_dl = devlink_priv(dl);

		bp_dl->bp = bp;
	पूर्ण
पूर्ण

#घोषणा NVM_OFF_MSIX_VEC_PER_PF_MAX	108
#घोषणा NVM_OFF_MSIX_VEC_PER_PF_MIN	114
#घोषणा NVM_OFF_IGNORE_ARI		164
#घोषणा NVM_OFF_DIS_GRE_VER_CHECK	171
#घोषणा NVM_OFF_ENABLE_SRIOV		401
#घोषणा NVM_OFF_NVM_CFG_VER		602

#घोषणा BNXT_NVM_CFG_VER_BITS		24
#घोषणा BNXT_NVM_CFG_VER_BYTES		4

#घोषणा BNXT_MSIX_VEC_MAX	512
#घोषणा BNXT_MSIX_VEC_MIN_MAX	128

क्रमागत bnxt_nvm_dir_type अणु
	BNXT_NVM_SHARED_CFG = 40,
	BNXT_NVM_PORT_CFG,
	BNXT_NVM_FUNC_CFG,
पूर्ण;

काष्ठा bnxt_dl_nvm_param अणु
	u16 id;
	u16 offset;
	u16 dir_type;
	u16 nvm_num_bits;
	u8 dl_num_bytes;
पूर्ण;

क्रमागत bnxt_dl_version_type अणु
	BNXT_VERSION_FIXED,
	BNXT_VERSION_RUNNING,
	BNXT_VERSION_STORED,
पूर्ण;

व्योम bnxt_devlink_health_report(काष्ठा bnxt *bp, अचिन्हित दीर्घ event);
व्योम bnxt_dl_health_status_update(काष्ठा bnxt *bp, bool healthy);
व्योम bnxt_dl_health_recovery_करोne(काष्ठा bnxt *bp);
व्योम bnxt_dl_fw_reporters_create(काष्ठा bnxt *bp);
व्योम bnxt_dl_fw_reporters_destroy(काष्ठा bnxt *bp, bool all);
पूर्णांक bnxt_dl_रेजिस्टर(काष्ठा bnxt *bp);
व्योम bnxt_dl_unरेजिस्टर(काष्ठा bnxt *bp);

#पूर्ण_अगर /* BNXT_DEVLINK_H */
