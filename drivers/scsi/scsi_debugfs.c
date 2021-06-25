<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/bitops.h>
#समावेश <linux/seq_file.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_dbg.h>
#समावेश "scsi_debugfs.h"

#घोषणा SCSI_CMD_FLAG_NAME(name)[स्थिर_ilog2(SCMD_##name)] = #name
अटल स्थिर अक्षर *स्थिर scsi_cmd_flags[] = अणु
	SCSI_CMD_FLAG_NAME(TAGGED),
	SCSI_CMD_FLAG_NAME(INITIALIZED),
पूर्ण;
#अघोषित SCSI_CMD_FLAG_NAME

अटल पूर्णांक scsi_flags_show(काष्ठा seq_file *m, स्थिर अचिन्हित दीर्घ flags,
			   स्थिर अक्षर *स्थिर *flag_name, पूर्णांक flag_name_count)
अणु
	bool sep = false;
	पूर्णांक i;

	क्रम_each_set_bit(i, &flags, BITS_PER_LONG) अणु
		अगर (sep)
			seq_माला_दो(m, "|");
		sep = true;
		अगर (i < flag_name_count && flag_name[i])
			seq_माला_दो(m, flag_name[i]);
		अन्यथा
			seq_म_लिखो(m, "%d", i);
	पूर्ण
	वापस 0;
पूर्ण

व्योम scsi_show_rq(काष्ठा seq_file *m, काष्ठा request *rq)
अणु
	काष्ठा scsi_cmnd *cmd = container_of(scsi_req(rq), typeof(*cmd), req);
	पूर्णांक alloc_ms = jअगरfies_to_msecs(jअगरfies - cmd->jअगरfies_at_alloc);
	पूर्णांक समयout_ms = jअगरfies_to_msecs(rq->समयout);
	स्थिर u8 *स्थिर cdb = READ_ONCE(cmd->cmnd);
	अक्षर buf[80] = "(?)";

	अगर (cdb)
		__scsi_क्रमmat_command(buf, माप(buf), cdb, cmd->cmd_len);
	seq_म_लिखो(m, ", .cmd=%s, .retries=%d, .result = %#x, .flags=", buf,
		   cmd->retries, cmd->result);
	scsi_flags_show(m, cmd->flags, scsi_cmd_flags,
			ARRAY_SIZE(scsi_cmd_flags));
	seq_म_लिखो(m, ", .timeout=%d.%03d, allocated %d.%03d s ago",
		   समयout_ms / 1000, समयout_ms % 1000,
		   alloc_ms / 1000, alloc_ms % 1000);
पूर्ण
