<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * libata-trace.c - trace functions क्रम libata
 *
 * Copyright 2015 Hannes Reinecke
 * Copyright 2015 SUSE Linux GmbH
 */

#समावेश <linux/kernel.h>
#समावेश <linux/trace_seq.h>
#समावेश <trace/events/libata.h>

स्थिर अक्षर *
libata_trace_parse_status(काष्ठा trace_seq *p, अचिन्हित अक्षर status)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);

	trace_seq_म_लिखो(p, "{ ");
	अगर (status & ATA_BUSY)
		trace_seq_म_लिखो(p, "BUSY ");
	अगर (status & ATA_DRDY)
		trace_seq_म_लिखो(p, "DRDY ");
	अगर (status & ATA_DF)
		trace_seq_म_लिखो(p, "DF ");
	अगर (status & ATA_DSC)
		trace_seq_म_लिखो(p, "DSC ");
	अगर (status & ATA_DRQ)
		trace_seq_म_लिखो(p, "DRQ ");
	अगर (status & ATA_CORR)
		trace_seq_म_लिखो(p, "CORR ");
	अगर (status & ATA_SENSE)
		trace_seq_म_लिखो(p, "SENSE ");
	अगर (status & ATA_ERR)
		trace_seq_म_लिखो(p, "ERR ");
	trace_seq_अ_दो(p, '}');
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

स्थिर अक्षर *
libata_trace_parse_eh_action(काष्ठा trace_seq *p, अचिन्हित पूर्णांक eh_action)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);

	trace_seq_म_लिखो(p, "%x", eh_action);
	अगर (eh_action) अणु
		trace_seq_म_लिखो(p, "{ ");
		अगर (eh_action & ATA_EH_REVALIDATE)
			trace_seq_म_लिखो(p, "REVALIDATE ");
		अगर (eh_action & (ATA_EH_SOFTRESET | ATA_EH_HARDRESET))
			trace_seq_म_लिखो(p, "RESET ");
		अन्यथा अगर (eh_action & ATA_EH_SOFTRESET)
			trace_seq_म_लिखो(p, "SOFTRESET ");
		अन्यथा अगर (eh_action & ATA_EH_HARDRESET)
			trace_seq_म_लिखो(p, "HARDRESET ");
		अगर (eh_action & ATA_EH_ENABLE_LINK)
			trace_seq_म_लिखो(p, "ENABLE_LINK ");
		अगर (eh_action & ATA_EH_PARK)
			trace_seq_म_लिखो(p, "PARK ");
		trace_seq_अ_दो(p, '}');
	पूर्ण
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

स्थिर अक्षर *
libata_trace_parse_eh_err_mask(काष्ठा trace_seq *p, अचिन्हित पूर्णांक eh_err_mask)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);

	trace_seq_म_लिखो(p, "%x", eh_err_mask);
	अगर (eh_err_mask) अणु
		trace_seq_म_लिखो(p, "{ ");
		अगर (eh_err_mask & AC_ERR_DEV)
			trace_seq_म_लिखो(p, "DEV ");
		अगर (eh_err_mask & AC_ERR_HSM)
			trace_seq_म_लिखो(p, "HSM ");
		अगर (eh_err_mask & AC_ERR_TIMEOUT)
			trace_seq_म_लिखो(p, "TIMEOUT ");
		अगर (eh_err_mask & AC_ERR_MEDIA)
			trace_seq_म_लिखो(p, "MEDIA ");
		अगर (eh_err_mask & AC_ERR_ATA_BUS)
			trace_seq_म_लिखो(p, "ATA_BUS ");
		अगर (eh_err_mask & AC_ERR_HOST_BUS)
			trace_seq_म_लिखो(p, "HOST_BUS ");
		अगर (eh_err_mask & AC_ERR_SYSTEM)
			trace_seq_म_लिखो(p, "SYSTEM ");
		अगर (eh_err_mask & AC_ERR_INVALID)
			trace_seq_म_लिखो(p, "INVALID ");
		अगर (eh_err_mask & AC_ERR_OTHER)
			trace_seq_म_लिखो(p, "OTHER ");
		अगर (eh_err_mask & AC_ERR_NODEV_HINT)
			trace_seq_म_लिखो(p, "NODEV_HINT ");
		अगर (eh_err_mask & AC_ERR_NCQ)
			trace_seq_म_लिखो(p, "NCQ ");
		trace_seq_अ_दो(p, '}');
	पूर्ण
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

स्थिर अक्षर *
libata_trace_parse_qc_flags(काष्ठा trace_seq *p, अचिन्हित पूर्णांक qc_flags)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);

	trace_seq_म_लिखो(p, "%x", qc_flags);
	अगर (qc_flags) अणु
		trace_seq_म_लिखो(p, "{ ");
		अगर (qc_flags & ATA_QCFLAG_ACTIVE)
			trace_seq_म_लिखो(p, "ACTIVE ");
		अगर (qc_flags & ATA_QCFLAG_DMAMAP)
			trace_seq_म_लिखो(p, "DMAMAP ");
		अगर (qc_flags & ATA_QCFLAG_IO)
			trace_seq_म_लिखो(p, "IO ");
		अगर (qc_flags & ATA_QCFLAG_RESULT_TF)
			trace_seq_म_लिखो(p, "RESULT_TF ");
		अगर (qc_flags & ATA_QCFLAG_CLEAR_EXCL)
			trace_seq_म_लिखो(p, "CLEAR_EXCL ");
		अगर (qc_flags & ATA_QCFLAG_QUIET)
			trace_seq_म_लिखो(p, "QUIET ");
		अगर (qc_flags & ATA_QCFLAG_RETRY)
			trace_seq_म_लिखो(p, "RETRY ");
		अगर (qc_flags & ATA_QCFLAG_FAILED)
			trace_seq_म_लिखो(p, "FAILED ");
		अगर (qc_flags & ATA_QCFLAG_SENSE_VALID)
			trace_seq_म_लिखो(p, "SENSE_VALID ");
		अगर (qc_flags & ATA_QCFLAG_EH_SCHEDULED)
			trace_seq_म_लिखो(p, "EH_SCHEDULED ");
		trace_seq_अ_दो(p, '}');
	पूर्ण
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

स्थिर अक्षर *
libata_trace_parse_subcmd(काष्ठा trace_seq *p, अचिन्हित अक्षर cmd,
			  अचिन्हित अक्षर feature, अचिन्हित अक्षर hob_nsect)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);

	चयन (cmd) अणु
	हाल ATA_CMD_FPDMA_RECV:
		चयन (hob_nsect & 0x5f) अणु
		हाल ATA_SUBCMD_FPDMA_RECV_RD_LOG_DMA_EXT:
			trace_seq_म_लिखो(p, " READ_LOG_DMA_EXT");
			अवरोध;
		हाल ATA_SUBCMD_FPDMA_RECV_ZAC_MGMT_IN:
			trace_seq_म_लिखो(p, " ZAC_MGMT_IN");
			अवरोध;
		पूर्ण
		अवरोध;
	हाल ATA_CMD_FPDMA_SEND:
		चयन (hob_nsect & 0x5f) अणु
		हाल ATA_SUBCMD_FPDMA_SEND_WR_LOG_DMA_EXT:
			trace_seq_म_लिखो(p, " WRITE_LOG_DMA_EXT");
			अवरोध;
		हाल ATA_SUBCMD_FPDMA_SEND_DSM:
			trace_seq_म_लिखो(p, " DATASET_MANAGEMENT");
			अवरोध;
		पूर्ण
		अवरोध;
	हाल ATA_CMD_NCQ_NON_DATA:
		चयन (feature) अणु
		हाल ATA_SUBCMD_NCQ_NON_DATA_ABORT_QUEUE:
			trace_seq_म_लिखो(p, " ABORT_QUEUE");
			अवरोध;
		हाल ATA_SUBCMD_NCQ_NON_DATA_SET_FEATURES:
			trace_seq_म_लिखो(p, " SET_FEATURES");
			अवरोध;
		हाल ATA_SUBCMD_NCQ_NON_DATA_ZERO_EXT:
			trace_seq_म_लिखो(p, " ZERO_EXT");
			अवरोध;
		हाल ATA_SUBCMD_NCQ_NON_DATA_ZAC_MGMT_OUT:
			trace_seq_म_लिखो(p, " ZAC_MGMT_OUT");
			अवरोध;
		पूर्ण
		अवरोध;
	हाल ATA_CMD_ZAC_MGMT_IN:
		चयन (feature) अणु
		हाल ATA_SUBCMD_ZAC_MGMT_IN_REPORT_ZONES:
			trace_seq_म_लिखो(p, " REPORT_ZONES");
			अवरोध;
		पूर्ण
		अवरोध;
	हाल ATA_CMD_ZAC_MGMT_OUT:
		चयन (feature) अणु
		हाल ATA_SUBCMD_ZAC_MGMT_OUT_CLOSE_ZONE:
			trace_seq_म_लिखो(p, " CLOSE_ZONE");
			अवरोध;
		हाल ATA_SUBCMD_ZAC_MGMT_OUT_FINISH_ZONE:
			trace_seq_म_लिखो(p, " FINISH_ZONE");
			अवरोध;
		हाल ATA_SUBCMD_ZAC_MGMT_OUT_OPEN_ZONE:
			trace_seq_म_लिखो(p, " OPEN_ZONE");
			अवरोध;
		हाल ATA_SUBCMD_ZAC_MGMT_OUT_RESET_WRITE_POINTER:
			trace_seq_म_लिखो(p, " RESET_WRITE_POINTER");
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण
