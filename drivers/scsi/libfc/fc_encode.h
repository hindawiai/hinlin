<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright(c) 2008 Intel Corporation. All rights reserved.
 *
 * Maपूर्णांकained at www.Open-FCoE.org
 */

#अगर_अघोषित _FC_ENCODE_H_
#घोषणा _FC_ENCODE_H_
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/utsname.h>
#समावेश <scsi/fc/fc_ms.h>

/*
 * F_CTL values क्रम simple requests and responses.
 */
#घोषणा FC_FCTL_REQ	(FC_FC_FIRST_SEQ | FC_FC_END_SEQ | FC_FC_SEQ_INIT)
#घोषणा FC_FCTL_RESP	(FC_FC_EX_CTX | FC_FC_LAST_SEQ | \
			FC_FC_END_SEQ | FC_FC_SEQ_INIT)

काष्ठा fc_ns_rft अणु
	काष्ठा fc_ns_fid fid;	/* port ID object */
	काष्ठा fc_ns_fts fts;	/* FC4-types object */
पूर्ण;

काष्ठा fc_ct_req अणु
	काष्ठा fc_ct_hdr hdr;
	जोड़ अणु
		काष्ठा fc_ns_gid_ft gid;
		काष्ठा fc_ns_rn_id  rn;
		काष्ठा fc_ns_rft rft;
		काष्ठा fc_ns_rff_id rff;
		काष्ठा fc_ns_fid fid;
		काष्ठा fc_ns_rsnn snn;
		काष्ठा fc_ns_rspn spn;
		काष्ठा fc_fdmi_rhba rhba;
		काष्ठा fc_fdmi_rpa  rpa;
		काष्ठा fc_fdmi_dprt dprt;
		काष्ठा fc_fdmi_dhba dhba;
	पूर्ण payload;
पूर्ण;

/**
 * fc_adisc_fill() - Fill in adisc request frame
 * @lport: local port.
 * @fp: fc frame where payload will be placed.
 */
अटल अंतरभूत व्योम fc_adisc_fill(काष्ठा fc_lport *lport, काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_els_adisc *adisc;

	adisc = fc_frame_payload_get(fp, माप(*adisc));
	स_रखो(adisc, 0, माप(*adisc));
	adisc->adisc_cmd = ELS_ADISC;
	put_unaligned_be64(lport->wwpn, &adisc->adisc_wwpn);
	put_unaligned_be64(lport->wwnn, &adisc->adisc_wwnn);
	hton24(adisc->adisc_port_id, lport->port_id);
पूर्ण

/**
 * fc_ct_hdr_fill- fills ct header and reset ct payload
 * वापसs poपूर्णांकer to ct request.
 */
अटल अंतरभूत काष्ठा fc_ct_req *fc_ct_hdr_fill(स्थिर काष्ठा fc_frame *fp,
					       अचिन्हित पूर्णांक op, माप_प्रकार req_size,
					       क्रमागत fc_ct_fs_type fs_type,
					       u8 subtype)
अणु
	काष्ठा fc_ct_req *ct;
	माप_प्रकार ct_plen;

	ct_plen  = माप(काष्ठा fc_ct_hdr) + req_size;
	ct = fc_frame_payload_get(fp, ct_plen);
	स_रखो(ct, 0, ct_plen);
	ct->hdr.ct_rev = FC_CT_REV;
	ct->hdr.ct_fs_type = fs_type;
	ct->hdr.ct_fs_subtype = subtype;
	ct->hdr.ct_cmd = htons((u16) op);
	वापस ct;
पूर्ण

/**
 * fc_ct_ns_fill() - Fill in a name service request frame
 * @lport: local port.
 * @fc_id: FC_ID of non-destination rport क्रम GPN_ID and similar inquiries.
 * @fp: frame to contain payload.
 * @op: CT opcode.
 * @r_ctl: poपूर्णांकer to FC header R_CTL.
 * @fh_type: poपूर्णांकer to FC-4 type.
 */
अटल अंतरभूत पूर्णांक fc_ct_ns_fill(काष्ठा fc_lport *lport,
		      u32 fc_id, काष्ठा fc_frame *fp,
		      अचिन्हित पूर्णांक op, क्रमागत fc_rctl *r_ctl,
		      क्रमागत fc_fh_type *fh_type)
अणु
	काष्ठा fc_ct_req *ct;
	माप_प्रकार len;

	चयन (op) अणु
	हाल FC_NS_GPN_FT:
		ct = fc_ct_hdr_fill(fp, op, माप(काष्ठा fc_ns_gid_ft),
				    FC_FST_सूची, FC_NS_SUBTYPE);
		ct->payload.gid.fn_fc4_type = FC_TYPE_FCP;
		अवरोध;

	हाल FC_NS_GPN_ID:
		ct = fc_ct_hdr_fill(fp, op, माप(काष्ठा fc_ns_fid),
				    FC_FST_सूची, FC_NS_SUBTYPE);
		ct->payload.gid.fn_fc4_type = FC_TYPE_FCP;
		hton24(ct->payload.fid.fp_fid, fc_id);
		अवरोध;

	हाल FC_NS_RFT_ID:
		ct = fc_ct_hdr_fill(fp, op, माप(काष्ठा fc_ns_rft),
				    FC_FST_सूची, FC_NS_SUBTYPE);
		hton24(ct->payload.rft.fid.fp_fid, lport->port_id);
		ct->payload.rft.fts = lport->fcts;
		अवरोध;

	हाल FC_NS_RFF_ID:
		ct = fc_ct_hdr_fill(fp, op, माप(काष्ठा fc_ns_rff_id),
				    FC_FST_सूची, FC_NS_SUBTYPE);
		hton24(ct->payload.rff.fr_fid.fp_fid, lport->port_id);
		ct->payload.rff.fr_type = FC_TYPE_FCP;
		अगर (lport->service_params & FCP_SPPF_INIT_FCN)
			ct->payload.rff.fr_feat = FCP_FEAT_INIT;
		अगर (lport->service_params & FCP_SPPF_TARG_FCN)
			ct->payload.rff.fr_feat |= FCP_FEAT_TARG;
		अवरोध;

	हाल FC_NS_RNN_ID:
		ct = fc_ct_hdr_fill(fp, op, माप(काष्ठा fc_ns_rn_id),
				    FC_FST_सूची, FC_NS_SUBTYPE);
		hton24(ct->payload.rn.fr_fid.fp_fid, lport->port_id);
		put_unaligned_be64(lport->wwnn, &ct->payload.rn.fr_wwn);
		अवरोध;

	हाल FC_NS_RSPN_ID:
		len = strnlen(fc_host_symbolic_name(lport->host), 255);
		ct = fc_ct_hdr_fill(fp, op, माप(काष्ठा fc_ns_rspn) + len,
				    FC_FST_सूची, FC_NS_SUBTYPE);
		hton24(ct->payload.spn.fr_fid.fp_fid, lport->port_id);
		म_नकलन(ct->payload.spn.fr_name,
			fc_host_symbolic_name(lport->host), len);
		ct->payload.spn.fr_name_len = len;
		अवरोध;

	हाल FC_NS_RSNN_NN:
		len = strnlen(fc_host_symbolic_name(lport->host), 255);
		ct = fc_ct_hdr_fill(fp, op, माप(काष्ठा fc_ns_rsnn) + len,
				    FC_FST_सूची, FC_NS_SUBTYPE);
		put_unaligned_be64(lport->wwnn, &ct->payload.snn.fr_wwn);
		म_नकलन(ct->payload.snn.fr_name,
			fc_host_symbolic_name(lport->host), len);
		ct->payload.snn.fr_name_len = len;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	*r_ctl = FC_RCTL_DD_UNSOL_CTL;
	*fh_type = FC_TYPE_CT;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम fc_ct_ms_fill_attr(काष्ठा fc_fdmi_attr_entry *entry,
				    स्थिर अक्षर *in, माप_प्रकार len)
अणु
	पूर्णांक copied = strscpy(entry->value, in, len);
	अगर (copied > 0)
		स_रखो(entry->value, copied, len - copied);
पूर्ण

/**
 * fc_ct_ms_fill() - Fill in a mgmt service request frame
 * @lport: local port.
 * @fc_id: FC_ID of non-destination rport क्रम GPN_ID and similar inquiries.
 * @fp: frame to contain payload.
 * @op: CT opcode.
 * @r_ctl: poपूर्णांकer to FC header R_CTL.
 * @fh_type: poपूर्णांकer to FC-4 type.
 */
अटल अंतरभूत पूर्णांक fc_ct_ms_fill(काष्ठा fc_lport *lport,
		      u32 fc_id, काष्ठा fc_frame *fp,
		      अचिन्हित पूर्णांक op, क्रमागत fc_rctl *r_ctl,
		      क्रमागत fc_fh_type *fh_type)
अणु
	काष्ठा fc_ct_req *ct;
	माप_प्रकार len;
	काष्ठा fc_fdmi_attr_entry *entry;
	काष्ठा fs_fdmi_attrs *hba_attrs;
	पूर्णांक numattrs = 0;

	चयन (op) अणु
	हाल FC_FDMI_RHBA:
		numattrs = 10;
		len = माप(काष्ठा fc_fdmi_rhba);
		len -= माप(काष्ठा fc_fdmi_attr_entry);
		len += (numattrs * FC_FDMI_ATTR_ENTRY_HEADER_LEN);
		len += FC_FDMI_HBA_ATTR_NODENAME_LEN;
		len += FC_FDMI_HBA_ATTR_MANUFACTURER_LEN;
		len += FC_FDMI_HBA_ATTR_SERIALNUMBER_LEN;
		len += FC_FDMI_HBA_ATTR_MODEL_LEN;
		len += FC_FDMI_HBA_ATTR_MODELDESCR_LEN;
		len += FC_FDMI_HBA_ATTR_HARDWAREVERSION_LEN;
		len += FC_FDMI_HBA_ATTR_DRIVERVERSION_LEN;
		len += FC_FDMI_HBA_ATTR_OPTIONROMVERSION_LEN;
		len += FC_FDMI_HBA_ATTR_FIRMWAREVERSION_LEN;
		len += FC_FDMI_HBA_ATTR_OSNAMEVERSION_LEN;
		ct = fc_ct_hdr_fill(fp, op, len, FC_FST_MGMT,
				    FC_FDMI_SUBTYPE);

		/* HBA Identअगरier */
		put_unaligned_be64(lport->wwpn, &ct->payload.rhba.hbaid.id);
		/* Number of Ports - always 1 */
		put_unaligned_be32(1, &ct->payload.rhba.port.numport);
		/* Port Name */
		put_unaligned_be64(lport->wwpn,
				   &ct->payload.rhba.port.port[0].portname);

		/* HBA Attributes */
		put_unaligned_be32(numattrs,
				   &ct->payload.rhba.hba_attrs.numattrs);
		hba_attrs = &ct->payload.rhba.hba_attrs;
		entry = (काष्ठा fc_fdmi_attr_entry *)hba_attrs->attr;
		/* NodeName*/
		len = FC_FDMI_ATTR_ENTRY_HEADER_LEN;
		len += FC_FDMI_HBA_ATTR_NODENAME_LEN;
		put_unaligned_be16(FC_FDMI_HBA_ATTR_NODENAME,
				   &entry->type);
		put_unaligned_be16(len, &entry->len);
		put_unaligned_be64(lport->wwnn,
				   (__be64 *)&entry->value[0]);

		/* Manufacturer */
		entry = (काष्ठा fc_fdmi_attr_entry *)((अक्षर *)entry->value +
					FC_FDMI_HBA_ATTR_NODENAME_LEN);
		len = FC_FDMI_ATTR_ENTRY_HEADER_LEN;
		len += FC_FDMI_HBA_ATTR_MANUFACTURER_LEN;
		put_unaligned_be16(FC_FDMI_HBA_ATTR_MANUFACTURER,
				   &entry->type);
		put_unaligned_be16(len, &entry->len);
		fc_ct_ms_fill_attr(entry,
			fc_host_manufacturer(lport->host),
			FC_FDMI_HBA_ATTR_MANUFACTURER_LEN);

		/* SerialNumber */
		entry = (काष्ठा fc_fdmi_attr_entry *)((अक्षर *)entry->value +
					FC_FDMI_HBA_ATTR_MANUFACTURER_LEN);
		len = FC_FDMI_ATTR_ENTRY_HEADER_LEN;
		len += FC_FDMI_HBA_ATTR_SERIALNUMBER_LEN;
		put_unaligned_be16(FC_FDMI_HBA_ATTR_SERIALNUMBER,
				   &entry->type);
		put_unaligned_be16(len, &entry->len);
		fc_ct_ms_fill_attr(entry,
			fc_host_serial_number(lport->host),
			FC_FDMI_HBA_ATTR_SERIALNUMBER_LEN);

		/* Model */
		entry = (काष्ठा fc_fdmi_attr_entry *)((अक्षर *)entry->value +
					FC_FDMI_HBA_ATTR_SERIALNUMBER_LEN);
		len = FC_FDMI_ATTR_ENTRY_HEADER_LEN;
		len += FC_FDMI_HBA_ATTR_MODEL_LEN;
		put_unaligned_be16(FC_FDMI_HBA_ATTR_MODEL,
				   &entry->type);
		put_unaligned_be16(len, &entry->len);
		fc_ct_ms_fill_attr(entry,
			fc_host_model(lport->host),
			FC_FDMI_HBA_ATTR_MODEL_LEN);

		/* Model Description */
		entry = (काष्ठा fc_fdmi_attr_entry *)((अक्षर *)entry->value +
					FC_FDMI_HBA_ATTR_MODEL_LEN);
		len = FC_FDMI_ATTR_ENTRY_HEADER_LEN;
		len += FC_FDMI_HBA_ATTR_MODELDESCR_LEN;
		put_unaligned_be16(FC_FDMI_HBA_ATTR_MODELDESCRIPTION,
				   &entry->type);
		put_unaligned_be16(len, &entry->len);
		fc_ct_ms_fill_attr(entry,
			fc_host_model_description(lport->host),
			FC_FDMI_HBA_ATTR_MODELDESCR_LEN);

		/* Hardware Version */
		entry = (काष्ठा fc_fdmi_attr_entry *)((अक्षर *)entry->value +
					FC_FDMI_HBA_ATTR_MODELDESCR_LEN);
		len = FC_FDMI_ATTR_ENTRY_HEADER_LEN;
		len += FC_FDMI_HBA_ATTR_HARDWAREVERSION_LEN;
		put_unaligned_be16(FC_FDMI_HBA_ATTR_HARDWAREVERSION,
				   &entry->type);
		put_unaligned_be16(len, &entry->len);
		fc_ct_ms_fill_attr(entry,
			fc_host_hardware_version(lport->host),
			FC_FDMI_HBA_ATTR_HARDWAREVERSION_LEN);

		/* Driver Version */
		entry = (काष्ठा fc_fdmi_attr_entry *)((अक्षर *)entry->value +
					FC_FDMI_HBA_ATTR_HARDWAREVERSION_LEN);
		len = FC_FDMI_ATTR_ENTRY_HEADER_LEN;
		len += FC_FDMI_HBA_ATTR_DRIVERVERSION_LEN;
		put_unaligned_be16(FC_FDMI_HBA_ATTR_DRIVERVERSION,
				   &entry->type);
		put_unaligned_be16(len, &entry->len);
		fc_ct_ms_fill_attr(entry,
			fc_host_driver_version(lport->host),
			FC_FDMI_HBA_ATTR_DRIVERVERSION_LEN);

		/* OptionROM Version */
		entry = (काष्ठा fc_fdmi_attr_entry *)((अक्षर *)entry->value +
					FC_FDMI_HBA_ATTR_DRIVERVERSION_LEN);
		len = FC_FDMI_ATTR_ENTRY_HEADER_LEN;
		len += FC_FDMI_HBA_ATTR_OPTIONROMVERSION_LEN;
		put_unaligned_be16(FC_FDMI_HBA_ATTR_OPTIONROMVERSION,
				   &entry->type);
		put_unaligned_be16(len, &entry->len);
		fc_ct_ms_fill_attr(entry,
			fc_host_optionrom_version(lport->host),
			FC_FDMI_HBA_ATTR_OPTIONROMVERSION_LEN);

		/* Firmware Version */
		entry = (काष्ठा fc_fdmi_attr_entry *)((अक्षर *)entry->value +
					FC_FDMI_HBA_ATTR_OPTIONROMVERSION_LEN);
		len = FC_FDMI_ATTR_ENTRY_HEADER_LEN;
		len += FC_FDMI_HBA_ATTR_FIRMWAREVERSION_LEN;
		put_unaligned_be16(FC_FDMI_HBA_ATTR_FIRMWAREVERSION,
				   &entry->type);
		put_unaligned_be16(len, &entry->len);
		fc_ct_ms_fill_attr(entry,
			fc_host_firmware_version(lport->host),
			FC_FDMI_HBA_ATTR_FIRMWAREVERSION_LEN);

		/* OS Name and Version */
		entry = (काष्ठा fc_fdmi_attr_entry *)((अक्षर *)entry->value +
					FC_FDMI_HBA_ATTR_FIRMWAREVERSION_LEN);
		len = FC_FDMI_ATTR_ENTRY_HEADER_LEN;
		len += FC_FDMI_HBA_ATTR_OSNAMEVERSION_LEN;
		put_unaligned_be16(FC_FDMI_HBA_ATTR_OSNAMEVERSION,
				   &entry->type);
		put_unaligned_be16(len, &entry->len);
		snम_लिखो((अक्षर *)&entry->value,
			FC_FDMI_HBA_ATTR_OSNAMEVERSION_LEN,
			"%s v%s",
			init_utsname()->sysname,
			init_utsname()->release);
		अवरोध;
	हाल FC_FDMI_RPA:
		numattrs = 6;
		len = माप(काष्ठा fc_fdmi_rpa);
		len -= माप(काष्ठा fc_fdmi_attr_entry);
		len += (numattrs * FC_FDMI_ATTR_ENTRY_HEADER_LEN);
		len += FC_FDMI_PORT_ATTR_FC4TYPES_LEN;
		len += FC_FDMI_PORT_ATTR_SUPPORTEDSPEED_LEN;
		len += FC_FDMI_PORT_ATTR_CURRENTPORTSPEED_LEN;
		len += FC_FDMI_PORT_ATTR_MAXFRAMESIZE_LEN;
		len += FC_FDMI_PORT_ATTR_OSDEVICENAME_LEN;
		len += FC_FDMI_PORT_ATTR_HOSTNAME_LEN;
		ct = fc_ct_hdr_fill(fp, op, len, FC_FST_MGMT,
				    FC_FDMI_SUBTYPE);

		/* Port Name */
		put_unaligned_be64(lport->wwpn,
				   &ct->payload.rpa.port.portname);

		/* Port Attributes */
		put_unaligned_be32(numattrs,
				   &ct->payload.rpa.hba_attrs.numattrs);

		hba_attrs = &ct->payload.rpa.hba_attrs;
		entry = (काष्ठा fc_fdmi_attr_entry *)hba_attrs->attr;

		/* FC4 types */
		len = FC_FDMI_ATTR_ENTRY_HEADER_LEN;
		len += FC_FDMI_PORT_ATTR_FC4TYPES_LEN;
		put_unaligned_be16(FC_FDMI_PORT_ATTR_FC4TYPES,
				   &entry->type);
		put_unaligned_be16(len, &entry->len);
		स_नकल(&entry->value, fc_host_supported_fc4s(lport->host),
		       FC_FDMI_PORT_ATTR_FC4TYPES_LEN);

		/* Supported Speed */
		entry = (काष्ठा fc_fdmi_attr_entry *)((अक्षर *)entry->value +
					FC_FDMI_PORT_ATTR_FC4TYPES_LEN);
		len = FC_FDMI_ATTR_ENTRY_HEADER_LEN;
		len += FC_FDMI_PORT_ATTR_SUPPORTEDSPEED_LEN;
		put_unaligned_be16(FC_FDMI_PORT_ATTR_SUPPORTEDSPEED,
				   &entry->type);
		put_unaligned_be16(len, &entry->len);

		put_unaligned_be32(fc_host_supported_speeds(lport->host),
				   &entry->value);

		/* Current Port Speed */
		entry = (काष्ठा fc_fdmi_attr_entry *)((अक्षर *)entry->value +
					FC_FDMI_PORT_ATTR_SUPPORTEDSPEED_LEN);
		len = FC_FDMI_ATTR_ENTRY_HEADER_LEN;
		len += FC_FDMI_PORT_ATTR_CURRENTPORTSPEED_LEN;
		put_unaligned_be16(FC_FDMI_PORT_ATTR_CURRENTPORTSPEED,
				   &entry->type);
		put_unaligned_be16(len, &entry->len);
		put_unaligned_be32(lport->link_speed,
				   &entry->value);

		/* Max Frame Size */
		entry = (काष्ठा fc_fdmi_attr_entry *)((अक्षर *)entry->value +
					FC_FDMI_PORT_ATTR_CURRENTPORTSPEED_LEN);
		len = FC_FDMI_ATTR_ENTRY_HEADER_LEN;
		len += FC_FDMI_PORT_ATTR_MAXFRAMESIZE_LEN;
		put_unaligned_be16(FC_FDMI_PORT_ATTR_MAXFRAMESIZE,
				   &entry->type);
		put_unaligned_be16(len, &entry->len);
		put_unaligned_be32(fc_host_maxframe_size(lport->host),
				   &entry->value);

		/* OS Device Name */
		entry = (काष्ठा fc_fdmi_attr_entry *)((अक्षर *)entry->value +
					FC_FDMI_PORT_ATTR_MAXFRAMESIZE_LEN);
		len = FC_FDMI_ATTR_ENTRY_HEADER_LEN;
		len += FC_FDMI_PORT_ATTR_OSDEVICENAME_LEN;
		put_unaligned_be16(FC_FDMI_PORT_ATTR_OSDEVICENAME,
				   &entry->type);
		put_unaligned_be16(len, &entry->len);
		/* Use the sysfs device name */
		fc_ct_ms_fill_attr(entry,
			dev_name(&lport->host->shost_gendev),
			strnlen(dev_name(&lport->host->shost_gendev),
				FC_FDMI_PORT_ATTR_HOSTNAME_LEN));

		/* Host Name */
		entry = (काष्ठा fc_fdmi_attr_entry *)((अक्षर *)entry->value +
					FC_FDMI_PORT_ATTR_OSDEVICENAME_LEN);
		len = FC_FDMI_ATTR_ENTRY_HEADER_LEN;
		len += FC_FDMI_PORT_ATTR_HOSTNAME_LEN;
		put_unaligned_be16(FC_FDMI_PORT_ATTR_HOSTNAME,
				   &entry->type);
		put_unaligned_be16(len, &entry->len);
		अगर (म_माप(fc_host_प्रणाली_hostname(lport->host)))
			fc_ct_ms_fill_attr(entry,
				fc_host_प्रणाली_hostname(lport->host),
				strnlen(fc_host_प्रणाली_hostname(lport->host),
					FC_FDMI_PORT_ATTR_HOSTNAME_LEN));
		अन्यथा
			fc_ct_ms_fill_attr(entry,
				init_utsname()->nodename,
				FC_FDMI_PORT_ATTR_HOSTNAME_LEN);
		अवरोध;
	हाल FC_FDMI_DPRT:
		len = माप(काष्ठा fc_fdmi_dprt);
		ct = fc_ct_hdr_fill(fp, op, len, FC_FST_MGMT,
				    FC_FDMI_SUBTYPE);
		/* Port Name */
		put_unaligned_be64(lport->wwpn,
				   &ct->payload.dprt.port.portname);
		अवरोध;
	हाल FC_FDMI_DHBA:
		len = माप(काष्ठा fc_fdmi_dhba);
		ct = fc_ct_hdr_fill(fp, op, len, FC_FST_MGMT,
				    FC_FDMI_SUBTYPE);
		/* HBA Identअगरier */
		put_unaligned_be64(lport->wwpn, &ct->payload.dhba.hbaid.id);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	*r_ctl = FC_RCTL_DD_UNSOL_CTL;
	*fh_type = FC_TYPE_CT;
	वापस 0;
पूर्ण

/**
 * fc_ct_fill() - Fill in a common transport service request frame
 * @lport: local port.
 * @fc_id: FC_ID of non-destination rport क्रम GPN_ID and similar inquiries.
 * @fp: frame to contain payload.
 * @op: CT opcode.
 * @r_ctl: poपूर्णांकer to FC header R_CTL.
 * @fh_type: poपूर्णांकer to FC-4 type.
 */
अटल अंतरभूत पूर्णांक fc_ct_fill(काष्ठा fc_lport *lport,
		      u32 fc_id, काष्ठा fc_frame *fp,
		      अचिन्हित पूर्णांक op, क्रमागत fc_rctl *r_ctl,
		      क्रमागत fc_fh_type *fh_type, u32 *did)
अणु
	पूर्णांक rc = -EINVAL;

	चयन (fc_id) अणु
	हाल FC_FID_MGMT_SERV:
		rc = fc_ct_ms_fill(lport, fc_id, fp, op, r_ctl, fh_type);
		*did = FC_FID_MGMT_SERV;
		अवरोध;
	हाल FC_FID_सूची_SERV:
	शेष:
		rc = fc_ct_ns_fill(lport, fc_id, fp, op, r_ctl, fh_type);
		*did = FC_FID_सूची_SERV;
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण
/**
 * fc_plogi_fill - Fill in plogi request frame
 */
अटल अंतरभूत व्योम fc_plogi_fill(काष्ठा fc_lport *lport, काष्ठा fc_frame *fp,
				 अचिन्हित पूर्णांक op)
अणु
	काष्ठा fc_els_flogi *plogi;
	काष्ठा fc_els_csp *csp;
	काष्ठा fc_els_cssp *cp;

	plogi = fc_frame_payload_get(fp, माप(*plogi));
	स_रखो(plogi, 0, माप(*plogi));
	plogi->fl_cmd = (u8) op;
	put_unaligned_be64(lport->wwpn, &plogi->fl_wwpn);
	put_unaligned_be64(lport->wwnn, &plogi->fl_wwnn);

	csp = &plogi->fl_csp;
	csp->sp_hi_ver = 0x20;
	csp->sp_lo_ver = 0x20;
	csp->sp_bb_cred = htons(10);	/* this माला_लो set by gateway */
	csp->sp_bb_data = htons((u16) lport->mfs);
	cp = &plogi->fl_cssp[3 - 1];	/* class 3 parameters */
	cp->cp_class = htons(FC_CPC_VALID | FC_CPC_SEQ);
	csp->sp_features = htons(FC_SP_FT_CIRO);
	csp->sp_tot_seq = htons(255);	/* seq. we accept */
	csp->sp_rel_off = htons(0x1f);
	csp->sp_e_d_tov = htonl(lport->e_d_tov);

	cp->cp_rdfs = htons((u16) lport->mfs);
	cp->cp_con_seq = htons(255);
	cp->cp_खोलो_seq = 1;
पूर्ण

/**
 * fc_flogi_fill - Fill in a flogi request frame.
 */
अटल अंतरभूत व्योम fc_flogi_fill(काष्ठा fc_lport *lport, काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_els_csp *sp;
	काष्ठा fc_els_cssp *cp;
	काष्ठा fc_els_flogi *flogi;

	flogi = fc_frame_payload_get(fp, माप(*flogi));
	स_रखो(flogi, 0, माप(*flogi));
	flogi->fl_cmd = (u8) ELS_FLOGI;
	put_unaligned_be64(lport->wwpn, &flogi->fl_wwpn);
	put_unaligned_be64(lport->wwnn, &flogi->fl_wwnn);
	sp = &flogi->fl_csp;
	sp->sp_hi_ver = 0x20;
	sp->sp_lo_ver = 0x20;
	sp->sp_bb_cred = htons(10);	/* this माला_लो set by gateway */
	sp->sp_bb_data = htons((u16) lport->mfs);
	cp = &flogi->fl_cssp[3 - 1];	/* class 3 parameters */
	cp->cp_class = htons(FC_CPC_VALID | FC_CPC_SEQ);
	अगर (lport->करोes_npiv)
		sp->sp_features = htons(FC_SP_FT_NPIV);
पूर्ण

/**
 * fc_fdisc_fill - Fill in a fdisc request frame.
 */
अटल अंतरभूत व्योम fc_fdisc_fill(काष्ठा fc_lport *lport, काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_els_csp *sp;
	काष्ठा fc_els_cssp *cp;
	काष्ठा fc_els_flogi *fdisc;

	fdisc = fc_frame_payload_get(fp, माप(*fdisc));
	स_रखो(fdisc, 0, माप(*fdisc));
	fdisc->fl_cmd = (u8) ELS_FDISC;
	put_unaligned_be64(lport->wwpn, &fdisc->fl_wwpn);
	put_unaligned_be64(lport->wwnn, &fdisc->fl_wwnn);
	sp = &fdisc->fl_csp;
	sp->sp_hi_ver = 0x20;
	sp->sp_lo_ver = 0x20;
	sp->sp_bb_cred = htons(10);	/* this माला_लो set by gateway */
	sp->sp_bb_data = htons((u16) lport->mfs);
	cp = &fdisc->fl_cssp[3 - 1];	/* class 3 parameters */
	cp->cp_class = htons(FC_CPC_VALID | FC_CPC_SEQ);
पूर्ण

/**
 * fc_logo_fill - Fill in a logo request frame.
 */
अटल अंतरभूत व्योम fc_logo_fill(काष्ठा fc_lport *lport, काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_els_logo *logo;

	logo = fc_frame_payload_get(fp, माप(*logo));
	स_रखो(logo, 0, माप(*logo));
	logo->fl_cmd = ELS_LOGO;
	hton24(logo->fl_n_port_id, lport->port_id);
	logo->fl_n_port_wwn = htonll(lport->wwpn);
पूर्ण

/**
 * fc_rtv_fill - Fill in RTV (पढ़ो समयout value) request frame.
 */
अटल अंतरभूत व्योम fc_rtv_fill(काष्ठा fc_lport *lport, काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_els_rtv *rtv;

	rtv = fc_frame_payload_get(fp, माप(*rtv));
	स_रखो(rtv, 0, माप(*rtv));
	rtv->rtv_cmd = ELS_RTV;
पूर्ण

/**
 * fc_rec_fill - Fill in rec request frame
 */
अटल अंतरभूत व्योम fc_rec_fill(काष्ठा fc_lport *lport, काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_els_rec *rec;
	काष्ठा fc_exch *ep = fc_seq_exch(fr_seq(fp));

	rec = fc_frame_payload_get(fp, माप(*rec));
	स_रखो(rec, 0, माप(*rec));
	rec->rec_cmd = ELS_REC;
	hton24(rec->rec_s_id, lport->port_id);
	rec->rec_ox_id = htons(ep->oxid);
	rec->rec_rx_id = htons(ep->rxid);
पूर्ण

/**
 * fc_prli_fill - Fill in prli request frame
 */
अटल अंतरभूत व्योम fc_prli_fill(काष्ठा fc_lport *lport, काष्ठा fc_frame *fp)
अणु
	काष्ठा अणु
		काष्ठा fc_els_prli prli;
		काष्ठा fc_els_spp spp;
	पूर्ण *pp;

	pp = fc_frame_payload_get(fp, माप(*pp));
	स_रखो(pp, 0, माप(*pp));
	pp->prli.prli_cmd = ELS_PRLI;
	pp->prli.prli_spp_len = माप(काष्ठा fc_els_spp);
	pp->prli.prli_len = htons(माप(*pp));
	pp->spp.spp_type = FC_TYPE_FCP;
	pp->spp.spp_flags = FC_SPP_EST_IMG_PAIR;
	pp->spp.spp_params = htonl(lport->service_params);
पूर्ण

/**
 * fc_scr_fill - Fill in a scr request frame.
 */
अटल अंतरभूत व्योम fc_scr_fill(काष्ठा fc_lport *lport, काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_els_scr *scr;

	scr = fc_frame_payload_get(fp, माप(*scr));
	स_रखो(scr, 0, माप(*scr));
	scr->scr_cmd = ELS_SCR;
	scr->scr_reg_func = ELS_SCRF_FULL;
पूर्ण

/**
 * fc_els_fill - Fill in an ELS  request frame
 */
अटल अंतरभूत पूर्णांक fc_els_fill(काष्ठा fc_lport *lport,
		       u32 did,
		       काष्ठा fc_frame *fp, अचिन्हित पूर्णांक op,
		       क्रमागत fc_rctl *r_ctl, क्रमागत fc_fh_type *fh_type)
अणु
	चयन (op) अणु
	हाल ELS_ADISC:
		fc_adisc_fill(lport, fp);
		अवरोध;

	हाल ELS_PLOGI:
		fc_plogi_fill(lport, fp, ELS_PLOGI);
		अवरोध;

	हाल ELS_FLOGI:
		fc_flogi_fill(lport, fp);
		अवरोध;

	हाल ELS_FDISC:
		fc_fdisc_fill(lport, fp);
		अवरोध;

	हाल ELS_LOGO:
		fc_logo_fill(lport, fp);
		अवरोध;

	हाल ELS_RTV:
		fc_rtv_fill(lport, fp);
		अवरोध;

	हाल ELS_REC:
		fc_rec_fill(lport, fp);
		अवरोध;

	हाल ELS_PRLI:
		fc_prli_fill(lport, fp);
		अवरोध;

	हाल ELS_SCR:
		fc_scr_fill(lport, fp);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	*r_ctl = FC_RCTL_ELS_REQ;
	*fh_type = FC_TYPE_ELS;
	वापस 0;
पूर्ण
#पूर्ण_अगर /* _FC_ENCODE_H_ */
