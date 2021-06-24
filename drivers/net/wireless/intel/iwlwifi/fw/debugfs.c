<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2012-2014, 2018-2020 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#समावेश "api/commands.h"
#समावेश "debugfs.h"
#समावेश "dbg.h"
#समावेश <linux/seq_file.h>

#घोषणा FWRT_DEBUGFS_OPEN_WRAPPER(name, buflen, argtype)		\
काष्ठा dbgfs_##name##_data अणु						\
	argtype *arg;							\
	bool पढ़ो_करोne;							\
	sमाप_प्रकार rlen;							\
	अक्षर rbuf[buflen];						\
पूर्ण;									\
अटल पूर्णांक _iwl_dbgfs_##name##_खोलो(काष्ठा inode *inode,		\
				    काष्ठा file *file)			\
अणु									\
	काष्ठा dbgfs_##name##_data *data;				\
									\
	data = kzalloc(माप(*data), GFP_KERNEL);			\
	अगर (!data)							\
		वापस -ENOMEM;						\
									\
	data->पढ़ो_करोne = false;					\
	data->arg = inode->i_निजी;					\
	file->निजी_data = data;					\
									\
	वापस 0;							\
पूर्ण

#घोषणा FWRT_DEBUGFS_READ_WRAPPER(name)					\
अटल sमाप_प्रकार _iwl_dbgfs_##name##_पढ़ो(काष्ठा file *file,		\
					अक्षर __user *user_buf,		\
					माप_प्रकार count, loff_t *ppos)	\
अणु									\
	काष्ठा dbgfs_##name##_data *data = file->निजी_data;		\
									\
	अगर (!data->पढ़ो_करोne) अणु						\
		data->पढ़ो_करोne = true;					\
		data->rlen = iwl_dbgfs_##name##_पढ़ो(data->arg,		\
						     माप(data->rbuf),\
						     data->rbuf);	\
	पूर्ण								\
									\
	अगर (data->rlen < 0)						\
		वापस data->rlen;					\
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos,		\
				       data->rbuf, data->rlen);		\
पूर्ण

अटल पूर्णांक _iwl_dbgfs_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	kमुक्त(file->निजी_data);

	वापस 0;
पूर्ण

#घोषणा _FWRT_DEBUGFS_READ_खाता_OPS(name, buflen, argtype)		\
FWRT_DEBUGFS_OPEN_WRAPPER(name, buflen, argtype)			\
FWRT_DEBUGFS_READ_WRAPPER(name)						\
अटल स्थिर काष्ठा file_operations iwl_dbgfs_##name##_ops = अणु		\
	.पढ़ो = _iwl_dbgfs_##name##_पढ़ो,				\
	.खोलो = _iwl_dbgfs_##name##_खोलो,				\
	.llseek = generic_file_llseek,					\
	.release = _iwl_dbgfs_release,					\
पूर्ण

#घोषणा FWRT_DEBUGFS_WRITE_WRAPPER(name, buflen, argtype)		\
अटल sमाप_प्रकार _iwl_dbgfs_##name##_ग_लिखो(काष्ठा file *file,		\
					 स्थिर अक्षर __user *user_buf,	\
					 माप_प्रकार count, loff_t *ppos)	\
अणु									\
	argtype *arg =							\
		((काष्ठा dbgfs_##name##_data *)file->निजी_data)->arg;\
	अक्षर buf[buflen] = अणुपूर्ण;						\
	माप_प्रकार buf_size = min(count, माप(buf) -  1);			\
									\
	अगर (copy_from_user(buf, user_buf, buf_size))			\
		वापस -EFAULT;						\
									\
	वापस iwl_dbgfs_##name##_ग_लिखो(arg, buf, buf_size);		\
पूर्ण

#घोषणा _FWRT_DEBUGFS_READ_WRITE_खाता_OPS(name, buflen, argtype)	\
FWRT_DEBUGFS_OPEN_WRAPPER(name, buflen, argtype)			\
FWRT_DEBUGFS_WRITE_WRAPPER(name, buflen, argtype)			\
FWRT_DEBUGFS_READ_WRAPPER(name)						\
अटल स्थिर काष्ठा file_operations iwl_dbgfs_##name##_ops = अणु		\
	.ग_लिखो = _iwl_dbgfs_##name##_ग_लिखो,				\
	.पढ़ो = _iwl_dbgfs_##name##_पढ़ो,				\
	.खोलो = _iwl_dbgfs_##name##_खोलो,				\
	.llseek = generic_file_llseek,					\
	.release = _iwl_dbgfs_release,					\
पूर्ण

#घोषणा _FWRT_DEBUGFS_WRITE_खाता_OPS(name, buflen, argtype)		\
FWRT_DEBUGFS_OPEN_WRAPPER(name, buflen, argtype)			\
FWRT_DEBUGFS_WRITE_WRAPPER(name, buflen, argtype)			\
अटल स्थिर काष्ठा file_operations iwl_dbgfs_##name##_ops = अणु		\
	.ग_लिखो = _iwl_dbgfs_##name##_ग_लिखो,				\
	.खोलो = _iwl_dbgfs_##name##_खोलो,				\
	.llseek = generic_file_llseek,					\
	.release = _iwl_dbgfs_release,					\
पूर्ण

#घोषणा FWRT_DEBUGFS_READ_खाता_OPS(name, bufsz)				\
	_FWRT_DEBUGFS_READ_खाता_OPS(name, bufsz, काष्ठा iwl_fw_runसमय)

#घोषणा FWRT_DEBUGFS_WRITE_खाता_OPS(name, bufsz)			\
	_FWRT_DEBUGFS_WRITE_खाता_OPS(name, bufsz, काष्ठा iwl_fw_runसमय)

#घोषणा FWRT_DEBUGFS_READ_WRITE_खाता_OPS(name, bufsz)			\
	_FWRT_DEBUGFS_READ_WRITE_खाता_OPS(name, bufsz, काष्ठा iwl_fw_runसमय)

#घोषणा FWRT_DEBUGFS_ADD_खाता_ALIAS(alias, name, parent, mode) करो अणु	\
	debugfs_create_file(alias, mode, parent, fwrt,			\
			    &iwl_dbgfs_##name##_ops);			\
	पूर्ण जबतक (0)
#घोषणा FWRT_DEBUGFS_ADD_खाता(name, parent, mode) \
	FWRT_DEBUGFS_ADD_खाता_ALIAS(#name, name, parent, mode)

अटल पूर्णांक iwl_fw_send_बारtamp_marker_cmd(काष्ठा iwl_fw_runसमय *fwrt)
अणु
	काष्ठा iwl_mvm_marker marker = अणु
		.dw_len = माप(काष्ठा iwl_mvm_marker) / 4,
		.marker_id = MARKER_ID_SYNC_CLOCK,

		/* the real बारtamp is taken from the ftrace घड़ी
		 * this is क्रम finding the match between fw and kernel logs
		 */
		.बारtamp = cpu_to_le64(fwrt->बारtamp.seq++),
	पूर्ण;

	काष्ठा iwl_host_cmd hcmd = अणु
		.id = MARKER_CMD,
		.flags = CMD_ASYNC,
		.data[0] = &marker,
		.len[0] = माप(marker),
	पूर्ण;

	वापस iwl_trans_send_cmd(fwrt->trans, &hcmd);
पूर्ण

अटल पूर्णांक iwl_dbgfs_enabled_severities_ग_लिखो(काष्ठा iwl_fw_runसमय *fwrt,
					      अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा iwl_dbg_host_event_cfg_cmd event_cfg;
	काष्ठा iwl_host_cmd hcmd = अणु
		.id = iwl_cmd_id(HOST_EVENT_CFG, DEBUG_GROUP, 0),
		.flags = CMD_ASYNC,
		.data[0] = &event_cfg,
		.len[0] = माप(event_cfg),
	पूर्ण;
	u32 enabled_severities;
	पूर्णांक ret = kstrtou32(buf, 10, &enabled_severities);

	अगर (ret < 0)
		वापस ret;

	event_cfg.enabled_severities = cpu_to_le32(enabled_severities);

	ret = iwl_trans_send_cmd(fwrt->trans, &hcmd);
	IWL_INFO(fwrt,
		 "sent host event cfg with enabled_severities: %u, ret: %d\n",
		 enabled_severities, ret);

	वापस ret ?: count;
पूर्ण

FWRT_DEBUGFS_WRITE_खाता_OPS(enabled_severities, 16);

अटल व्योम iwl_fw_बारtamp_marker_wk(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक ret;
	काष्ठा iwl_fw_runसमय *fwrt =
		container_of(work, काष्ठा iwl_fw_runसमय, बारtamp.wk.work);
	अचिन्हित दीर्घ delay = fwrt->बारtamp.delay;

	ret = iwl_fw_send_बारtamp_marker_cmd(fwrt);
	अगर (!ret && delay)
		schedule_delayed_work(&fwrt->बारtamp.wk,
				      round_jअगरfies_relative(delay));
	अन्यथा
		IWL_INFO(fwrt,
			 "stopping timestamp_marker, ret: %d, delay: %u\n",
			 ret, jअगरfies_to_msecs(delay) / 1000);
पूर्ण

व्योम iwl_fw_trigger_बारtamp(काष्ठा iwl_fw_runसमय *fwrt, u32 delay)
अणु
	IWL_INFO(fwrt,
		 "starting timestamp_marker trigger with delay: %us\n",
		 delay);

	iwl_fw_cancel_बारtamp(fwrt);

	fwrt->बारtamp.delay = msecs_to_jअगरfies(delay * 1000);

	schedule_delayed_work(&fwrt->बारtamp.wk,
			      round_jअगरfies_relative(fwrt->बारtamp.delay));
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_बारtamp_marker_ग_लिखो(काष्ठा iwl_fw_runसमय *fwrt,
						अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;
	u32 delay;

	ret = kstrtou32(buf, 10, &delay);
	अगर (ret < 0)
		वापस ret;

	iwl_fw_trigger_बारtamp(fwrt, delay);

	वापस count;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_बारtamp_marker_पढ़ो(काष्ठा iwl_fw_runसमय *fwrt,
					       माप_प्रकार size, अक्षर *buf)
अणु
	u32 delay_secs = jअगरfies_to_msecs(fwrt->बारtamp.delay) / 1000;

	वापस scnम_लिखो(buf, size, "%d\n", delay_secs);
पूर्ण

FWRT_DEBUGFS_READ_WRITE_खाता_OPS(बारtamp_marker, 16);

काष्ठा hcmd_ग_लिखो_data अणु
	__be32 cmd_id;
	__be32 flags;
	__be16 length;
	u8 data[];
पूर्ण __packed;

अटल sमाप_प्रकार iwl_dbgfs_send_hcmd_ग_लिखो(काष्ठा iwl_fw_runसमय *fwrt, अक्षर *buf,
					 माप_प्रकार count)
अणु
	माप_प्रकार header_size = (माप(u32) * 2 + माप(u16)) * 2;
	माप_प्रकार data_size = (count - 1) / 2;
	पूर्णांक ret;
	काष्ठा hcmd_ग_लिखो_data *data;
	काष्ठा iwl_host_cmd hcmd = अणु
		.len = अणु 0, पूर्ण,
		.data = अणु शून्य, पूर्ण,
	पूर्ण;

	अगर (fwrt->ops && fwrt->ops->fw_running &&
	    !fwrt->ops->fw_running(fwrt->ops_ctx))
		वापस -EIO;

	अगर (count < header_size + 1 || count > 1024 * 4)
		वापस -EINVAL;

	data = kदो_स्मृति(data_size, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	ret = hex2bin((u8 *)data, buf, data_size);
	अगर (ret)
		जाओ out;

	hcmd.id = be32_to_cpu(data->cmd_id);
	hcmd.flags = be32_to_cpu(data->flags);
	hcmd.len[0] = be16_to_cpu(data->length);
	hcmd.data[0] = data->data;

	अगर (count != header_size + hcmd.len[0] * 2 + 1) अणु
		IWL_ERR(fwrt,
			"host command data size does not match header length\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (fwrt->ops && fwrt->ops->send_hcmd)
		ret = fwrt->ops->send_hcmd(fwrt->ops_ctx, &hcmd);
	अन्यथा
		ret = -EPERM;

	अगर (ret < 0)
		जाओ out;

	अगर (hcmd.flags & CMD_WANT_SKB)
		iwl_मुक्त_resp(&hcmd);
out:
	kमुक्त(data);
	वापस ret ?: count;
पूर्ण

FWRT_DEBUGFS_WRITE_खाता_OPS(send_hcmd, 512);

अटल sमाप_प्रकार iwl_dbgfs_fw_dbg_करोमुख्य_पढ़ो(काष्ठा iwl_fw_runसमय *fwrt,
					    माप_प्रकार size, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, size, "0x%08x\n",
			 fwrt->trans->dbg.करोमुख्यs_biपंचांगap);
पूर्ण

FWRT_DEBUGFS_READ_खाता_OPS(fw_dbg_करोमुख्य, 20);

काष्ठा iwl_dbgfs_fw_info_priv अणु
	काष्ठा iwl_fw_runसमय *fwrt;
पूर्ण;

काष्ठा iwl_dbgfs_fw_info_state अणु
	loff_t pos;
पूर्ण;

अटल व्योम *iwl_dbgfs_fw_info_seq_next(काष्ठा seq_file *seq,
					व्योम *v, loff_t *pos)
अणु
	काष्ठा iwl_dbgfs_fw_info_state *state = v;
	काष्ठा iwl_dbgfs_fw_info_priv *priv = seq->निजी;
	स्थिर काष्ठा iwl_fw *fw = priv->fwrt->fw;

	*pos = ++state->pos;
	अगर (*pos >= fw->ucode_capa.n_cmd_versions)
		वापस शून्य;

	वापस state;
पूर्ण

अटल व्योम iwl_dbgfs_fw_info_seq_stop(काष्ठा seq_file *seq,
				       व्योम *v)
अणु
	kमुक्त(v);
पूर्ण

अटल व्योम *iwl_dbgfs_fw_info_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा iwl_dbgfs_fw_info_priv *priv = seq->निजी;
	स्थिर काष्ठा iwl_fw *fw = priv->fwrt->fw;
	काष्ठा iwl_dbgfs_fw_info_state *state;

	अगर (*pos >= fw->ucode_capa.n_cmd_versions)
		वापस शून्य;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;
	state->pos = *pos;
	वापस state;
पूर्ण;

अटल पूर्णांक iwl_dbgfs_fw_info_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा iwl_dbgfs_fw_info_state *state = v;
	काष्ठा iwl_dbgfs_fw_info_priv *priv = seq->निजी;
	स्थिर काष्ठा iwl_fw *fw = priv->fwrt->fw;
	स्थिर काष्ठा iwl_fw_cmd_version *ver;
	u32 cmd_id;

	अगर (!state->pos)
		seq_माला_दो(seq, "fw_api_ver:\n");

	ver = &fw->ucode_capa.cmd_versions[state->pos];

	cmd_id = iwl_cmd_id(ver->cmd, ver->group, 0);

	seq_म_लिखो(seq, "  0x%04x:\n", cmd_id);
	seq_म_लिखो(seq, "    name: %s\n",
		   iwl_get_cmd_string(priv->fwrt->trans, cmd_id));
	seq_म_लिखो(seq, "    cmd_ver: %d\n", ver->cmd_ver);
	seq_म_लिखो(seq, "    notif_ver: %d\n", ver->notअगर_ver);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations iwl_dbgfs_info_seq_ops = अणु
	.start = iwl_dbgfs_fw_info_seq_start,
	.next = iwl_dbgfs_fw_info_seq_next,
	.stop = iwl_dbgfs_fw_info_seq_stop,
	.show = iwl_dbgfs_fw_info_seq_show,
पूर्ण;

अटल पूर्णांक iwl_dbgfs_fw_info_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा iwl_dbgfs_fw_info_priv *priv;

	priv = __seq_खोलो_निजी(filp, &iwl_dbgfs_info_seq_ops,
				  माप(*priv));

	अगर (!priv)
		वापस -ENOMEM;

	priv->fwrt = inode->i_निजी;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations iwl_dbgfs_fw_info_ops = अणु
	.owner = THIS_MODULE,
	.खोलो = iwl_dbgfs_fw_info_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = seq_release_निजी,
पूर्ण;

व्योम iwl_fwrt_dbgfs_रेजिस्टर(काष्ठा iwl_fw_runसमय *fwrt,
			    काष्ठा dentry *dbgfs_dir)
अणु
	INIT_DELAYED_WORK(&fwrt->बारtamp.wk, iwl_fw_बारtamp_marker_wk);
	FWRT_DEBUGFS_ADD_खाता(बारtamp_marker, dbgfs_dir, 0200);
	FWRT_DEBUGFS_ADD_खाता(fw_info, dbgfs_dir, 0200);
	FWRT_DEBUGFS_ADD_खाता(send_hcmd, dbgfs_dir, 0200);
	FWRT_DEBUGFS_ADD_खाता(enabled_severities, dbgfs_dir, 0200);
	FWRT_DEBUGFS_ADD_खाता(fw_dbg_करोमुख्य, dbgfs_dir, 0400);
पूर्ण
