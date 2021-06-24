<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause) */
/*
 * Copyright 2013-2016 Freescale Semiconductor Inc.
 * Copyright 2016 NXP
 *
 */
#अगर_अघोषित __FSL_DPIO_H
#घोषणा __FSL_DPIO_H

काष्ठा fsl_mc_io;

पूर्णांक dpio_खोलो(काष्ठा fsl_mc_io	*mc_io,
	      u32		cmd_flags,
	      पूर्णांक		dpio_id,
	      u16		*token);

पूर्णांक dpio_बंद(काष्ठा fsl_mc_io	*mc_io,
	       u32		cmd_flags,
	       u16		token);

/**
 * क्रमागत dpio_channel_mode - DPIO notअगरication channel mode
 * @DPIO_NO_CHANNEL: No support क्रम notअगरication channel
 * @DPIO_LOCAL_CHANNEL: Notअगरications on data availability can be received by a
 *	dedicated channel in the DPIO; user should poपूर्णांक the queue's
 *	destination in the relevant पूर्णांकerface to this DPIO
 */
क्रमागत dpio_channel_mode अणु
	DPIO_NO_CHANNEL = 0,
	DPIO_LOCAL_CHANNEL = 1,
पूर्ण;

/**
 * काष्ठा dpio_cfg - Structure representing DPIO configuration
 * @channel_mode: Notअगरication channel mode
 * @num_priorities: Number of priorities क्रम the notअगरication channel (1-8);
 *			relevant only अगर 'channel_mode = DPIO_LOCAL_CHANNEL'
 */
काष्ठा dpio_cfg अणु
	क्रमागत dpio_channel_mode	channel_mode;
	u8		num_priorities;
पूर्ण;

पूर्णांक dpio_enable(काष्ठा fsl_mc_io	*mc_io,
		u32		cmd_flags,
		u16		token);

पूर्णांक dpio_disable(काष्ठा fsl_mc_io	*mc_io,
		 u32		cmd_flags,
		 u16		token);

/**
 * काष्ठा dpio_attr - Structure representing DPIO attributes
 * @id: DPIO object ID
 * @qbman_portal_ce_offset: offset of the software portal cache-enabled area
 * @qbman_portal_ci_offset: offset of the software portal cache-inhibited area
 * @qbman_portal_id: Software portal ID
 * @channel_mode: Notअगरication channel mode
 * @num_priorities: Number of priorities क्रम the notअगरication channel (1-8);
 *			relevant only अगर 'channel_mode = DPIO_LOCAL_CHANNEL'
 * @qbman_version: QBMAN version
 */
काष्ठा dpio_attr अणु
	पूर्णांक			id;
	u64		qbman_portal_ce_offset;
	u64		qbman_portal_ci_offset;
	u16		qbman_portal_id;
	क्रमागत dpio_channel_mode	channel_mode;
	u8			num_priorities;
	u32		qbman_version;
पूर्ण;

पूर्णांक dpio_get_attributes(काष्ठा fsl_mc_io	*mc_io,
			u32		cmd_flags,
			u16		token,
			काष्ठा dpio_attr	*attr);

पूर्णांक dpio_set_stashing_destination(काष्ठा fsl_mc_io *mc_io,
				  u32 cmd_flags,
				  u16 token,
				  u8 dest);

पूर्णांक dpio_get_api_version(काष्ठा fsl_mc_io *mc_io,
			 u32 cmd_flags,
			 u16 *major_ver,
			 u16 *minor_ver);

पूर्णांक dpio_reset(काष्ठा fsl_mc_io	*mc_io,
	       u32 cmd_flags,
	       u16 token);

#पूर्ण_अगर /* __FSL_DPIO_H */
