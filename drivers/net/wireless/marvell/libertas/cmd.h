<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2007, Red Hat, Inc. */

#अगर_अघोषित _LBS_CMD_H_
#घोषणा _LBS_CMD_H_

#समावेश <net/cfg80211.h>

#समावेश "host.h"
#समावेश "dev.h"


/* Command & response transfer between host and card */

काष्ठा cmd_ctrl_node अणु
	काष्ठा list_head list;
	पूर्णांक result;
	/* command response */
	पूर्णांक (*callback)(काष्ठा lbs_निजी *,
			अचिन्हित दीर्घ,
			काष्ठा cmd_header *);
	अचिन्हित दीर्घ callback_arg;
	/* command data */
	काष्ठा cmd_header *cmdbuf;
	/* रुको queue */
	u16 cmdरुकोqwoken;
	रुको_queue_head_t cmdरुको_q;
पूर्ण;


/* lbs_cmd() infers the size of the buffer to copy data back पूर्णांकo, from
   the size of the target of the poपूर्णांकer. Since the command to be sent
   may often be smaller, that size is set in cmd->size by the caller.*/
#घोषणा lbs_cmd(priv, cmdnr, cmd, cb, cb_arg)	(अणु		\
	uपूर्णांक16_t __sz = le16_to_cpu((cmd)->hdr.size);		\
	(cmd)->hdr.size = cpu_to_le16(माप(*(cmd)));		\
	__lbs_cmd(priv, cmdnr, &(cmd)->hdr, __sz, cb, cb_arg);	\
पूर्ण)

#घोषणा lbs_cmd_with_response(priv, cmdnr, cmd)	\
	lbs_cmd(priv, cmdnr, cmd, lbs_cmd_copyback, (अचिन्हित दीर्घ) (cmd))

व्योम lbs_cmd_async(काष्ठा lbs_निजी *priv, uपूर्णांक16_t command,
	काष्ठा cmd_header *in_cmd, पूर्णांक in_cmd_size);

पूर्णांक __lbs_cmd(काष्ठा lbs_निजी *priv, uपूर्णांक16_t command,
	      काष्ठा cmd_header *in_cmd, पूर्णांक in_cmd_size,
	      पूर्णांक (*callback)(काष्ठा lbs_निजी *, अचिन्हित दीर्घ, काष्ठा cmd_header *),
	      अचिन्हित दीर्घ callback_arg);

काष्ठा cmd_ctrl_node *__lbs_cmd_async(काष्ठा lbs_निजी *priv,
	uपूर्णांक16_t command, काष्ठा cmd_header *in_cmd, पूर्णांक in_cmd_size,
	पूर्णांक (*callback)(काष्ठा lbs_निजी *, अचिन्हित दीर्घ, काष्ठा cmd_header *),
	अचिन्हित दीर्घ callback_arg);

पूर्णांक lbs_cmd_copyback(काष्ठा lbs_निजी *priv, अचिन्हित दीर्घ extra,
		     काष्ठा cmd_header *resp);

पूर्णांक lbs_allocate_cmd_buffer(काष्ठा lbs_निजी *priv);
पूर्णांक lbs_मुक्त_cmd_buffer(काष्ठा lbs_निजी *priv);

पूर्णांक lbs_execute_next_command(काष्ठा lbs_निजी *priv);
व्योम __lbs_complete_command(काष्ठा lbs_निजी *priv, काष्ठा cmd_ctrl_node *cmd,
			    पूर्णांक result);
व्योम lbs_complete_command(काष्ठा lbs_निजी *priv, काष्ठा cmd_ctrl_node *cmd,
			  पूर्णांक result);
पूर्णांक lbs_process_command_response(काष्ठा lbs_निजी *priv, u8 *data, u32 len);


/* From cmdresp.c */

व्योम lbs_mac_event_disconnected(काष्ठा lbs_निजी *priv,
				bool locally_generated);



/* Events */

व्योम lbs_process_event(काष्ठा lbs_निजी *priv, u32 event);


/* Actual commands */

पूर्णांक lbs_update_hw_spec(काष्ठा lbs_निजी *priv);

पूर्णांक lbs_set_channel(काष्ठा lbs_निजी *priv, u8 channel);

पूर्णांक lbs_update_channel(काष्ठा lbs_निजी *priv);

पूर्णांक lbs_host_sleep_cfg(काष्ठा lbs_निजी *priv, uपूर्णांक32_t criteria,
		काष्ठा wol_config *p_wol_config);

पूर्णांक lbs_cmd_802_11_sleep_params(काष्ठा lbs_निजी *priv, uपूर्णांक16_t cmd_action,
				काष्ठा sleep_params *sp);

व्योम lbs_ps_confirm_sleep(काष्ठा lbs_निजी *priv);

पूर्णांक lbs_set_radio(काष्ठा lbs_निजी *priv, u8 preamble, u8 radio_on);

व्योम lbs_set_mac_control(काष्ठा lbs_निजी *priv);
पूर्णांक lbs_set_mac_control_sync(काष्ठा lbs_निजी *priv);

पूर्णांक lbs_get_tx_घातer(काष्ठा lbs_निजी *priv, s16 *curlevel, s16 *minlevel,
		     s16 *maxlevel);

पूर्णांक lbs_set_snmp_mib(काष्ठा lbs_निजी *priv, u32 oid, u16 val);

पूर्णांक lbs_get_snmp_mib(काष्ठा lbs_निजी *priv, u32 oid, u16 *out_val);


/* Commands only used in wext.c, assoc. and scan.c */

पूर्णांक lbs_set_घातer_adapt_cfg(काष्ठा lbs_निजी *priv, पूर्णांक enable, पूर्णांक8_t p0,
		पूर्णांक8_t p1, पूर्णांक8_t p2);

पूर्णांक lbs_set_tpc_cfg(काष्ठा lbs_निजी *priv, पूर्णांक enable, पूर्णांक8_t p0, पूर्णांक8_t p1,
		पूर्णांक8_t p2, पूर्णांक usesnr);

पूर्णांक lbs_set_data_rate(काष्ठा lbs_निजी *priv, u8 rate);

पूर्णांक lbs_cmd_802_11_rate_adapt_rateset(काष्ठा lbs_निजी *priv,
				      uपूर्णांक16_t cmd_action);

पूर्णांक lbs_set_tx_घातer(काष्ठा lbs_निजी *priv, s16 dbm);

पूर्णांक lbs_set_deep_sleep(काष्ठा lbs_निजी *priv, पूर्णांक deep_sleep);

पूर्णांक lbs_set_host_sleep(काष्ठा lbs_निजी *priv, पूर्णांक host_sleep);

पूर्णांक lbs_set_monitor_mode(काष्ठा lbs_निजी *priv, पूर्णांक enable);

पूर्णांक lbs_get_rssi(काष्ठा lbs_निजी *priv, s8 *snr, s8 *nf);

पूर्णांक lbs_set_11d_करोमुख्य_info(काष्ठा lbs_निजी *priv);

पूर्णांक lbs_get_reg(काष्ठा lbs_निजी *priv, u16 reg, u16 offset, u32 *value);

पूर्णांक lbs_set_reg(काष्ठा lbs_निजी *priv, u16 reg, u16 offset, u32 value);

पूर्णांक lbs_set_ps_mode(काष्ठा lbs_निजी *priv, u16 cmd_action, bool block);

#पूर्ण_अगर /* _LBS_CMD_H */
