<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2016-2019, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित __SOC_QCOM_TCS_H__
#घोषणा __SOC_QCOM_TCS_H__

#घोषणा MAX_RPMH_PAYLOAD	16

/**
 * rpmh_state: state क्रम the request
 *
 * RPMH_SLEEP_STATE:       State of the resource when the processor subप्रणाली
 *                         is घातered करोwn. There is no client using the
 *                         resource actively.
 * RPMH_WAKE_ONLY_STATE:   Resume resource state to the value previously
 *                         requested beक्रमe the processor was घातered करोwn.
 * RPMH_ACTIVE_ONLY_STATE: Active or AMC mode requests. Resource state
 *                         is aggregated immediately.
 */
क्रमागत rpmh_state अणु
	RPMH_SLEEP_STATE,
	RPMH_WAKE_ONLY_STATE,
	RPMH_ACTIVE_ONLY_STATE,
पूर्ण;

/**
 * काष्ठा tcs_cmd: an inभागidual request to RPMH.
 *
 * @addr: the address of the resource slv_id:18:16 | offset:0:15
 * @data: the resource state request
 * @रुको: ensure that this command is complete beक्रमe वापसing.
 *        Setting "wait" here only makes sense during rpmh_ग_लिखो_batch() क्रम
 *        active-only transfers, this is because:
 *        rpmh_ग_लिखो() - Always रुकोs.
 *                       (DEFINE_RPMH_MSG_ONSTACK will set .रुको_क्रम_compl)
 *        rpmh_ग_लिखो_async() - Never रुकोs.
 *                       (There's no request completion callback)
 */
काष्ठा tcs_cmd अणु
	u32 addr;
	u32 data;
	u32 रुको;
पूर्ण;

/**
 * काष्ठा tcs_request: A set of tcs_cmds sent together in a TCS
 *
 * @state:          state क्रम the request.
 * @रुको_क्रम_compl: रुको until we get a response from the h/w accelerator
 *                  (same as setting cmd->रुको क्रम all commands in the request)
 * @num_cmds:       the number of @cmds in this request
 * @cmds:           an array of tcs_cmds
 */
काष्ठा tcs_request अणु
	क्रमागत rpmh_state state;
	u32 रुको_क्रम_compl;
	u32 num_cmds;
	काष्ठा tcs_cmd *cmds;
पूर्ण;

#घोषणा BCM_TCS_CMD_COMMIT_SHFT		30
#घोषणा BCM_TCS_CMD_COMMIT_MASK		0x40000000
#घोषणा BCM_TCS_CMD_VALID_SHFT		29
#घोषणा BCM_TCS_CMD_VALID_MASK		0x20000000
#घोषणा BCM_TCS_CMD_VOTE_X_SHFT		14
#घोषणा BCM_TCS_CMD_VOTE_MASK		0x3fff
#घोषणा BCM_TCS_CMD_VOTE_Y_SHFT		0
#घोषणा BCM_TCS_CMD_VOTE_Y_MASK		0xfffc000

/* Conकाष्ठा a Bus Clock Manager (BCM) specअगरic TCS command */
#घोषणा BCM_TCS_CMD(commit, valid, vote_x, vote_y)		\
	(((commit) << BCM_TCS_CMD_COMMIT_SHFT) |		\
	((valid) << BCM_TCS_CMD_VALID_SHFT) |			\
	((cpu_to_le32(vote_x) &					\
	BCM_TCS_CMD_VOTE_MASK) << BCM_TCS_CMD_VOTE_X_SHFT) |	\
	((cpu_to_le32(vote_y) &					\
	BCM_TCS_CMD_VOTE_MASK) << BCM_TCS_CMD_VOTE_Y_SHFT))

#पूर्ण_अगर /* __SOC_QCOM_TCS_H__ */
