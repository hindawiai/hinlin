<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2012 Broadcom Corporation
 */

/* FWIL is the Firmware Interface Layer. In this module the support functions
 * are located to set and get variables to and from the firmware.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <brcmu_utils.h>
#समावेश <brcmu_wअगरi.h>
#समावेश "core.h"
#समावेश "bus.h"
#समावेश "debug.h"
#समावेश "tracepoint.h"
#समावेश "fwil.h"
#समावेश "proto.h"


#घोषणा MAX_HEX_DUMP_LEN	64

#अगर_घोषित DEBUG
अटल स्थिर अक्षर * स्थिर brcmf_fil_errstr[] = अणु
	"BCME_OK",
	"BCME_ERROR",
	"BCME_BADARG",
	"BCME_BADOPTION",
	"BCME_NOTUP",
	"BCME_NOTDOWN",
	"BCME_NOTAP",
	"BCME_NOTSTA",
	"BCME_BADKEYIDX",
	"BCME_RADIOOFF",
	"BCME_NOTBANDLOCKED",
	"BCME_NOCLK",
	"BCME_BADRATESET",
	"BCME_BADBAND",
	"BCME_BUFTOOSHORT",
	"BCME_BUFTOOLONG",
	"BCME_BUSY",
	"BCME_NOTASSOCIATED",
	"BCME_BADSSIDLEN",
	"BCME_OUTOFRANGECHAN",
	"BCME_BADCHAN",
	"BCME_BADADDR",
	"BCME_NORESOURCE",
	"BCME_UNSUPPORTED",
	"BCME_BADLEN",
	"BCME_NOTREADY",
	"BCME_EPERM",
	"BCME_NOMEM",
	"BCME_ASSOCIATED",
	"BCME_RANGE",
	"BCME_NOTFOUND",
	"BCME_WME_NOT_ENABLED",
	"BCME_TSPEC_NOTFOUND",
	"BCME_ACM_NOTSUPPORTED",
	"BCME_NOT_WME_ASSOCIATION",
	"BCME_SDIO_ERROR",
	"BCME_DONGLE_DOWN",
	"BCME_VERSION",
	"BCME_TXFAIL",
	"BCME_RXFAIL",
	"BCME_NODEVICE",
	"BCME_NMODE_DISABLED",
	"BCME_NONRESIDENT",
	"BCME_SCANREJECT",
	"BCME_USAGE_ERROR",
	"BCME_IOCTL_ERROR",
	"BCME_SERIAL_PORT_ERR",
	"BCME_DISABLED",
	"BCME_DECERR",
	"BCME_ENCERR",
	"BCME_MICERR",
	"BCME_REPLAY",
	"BCME_IE_NOTFOUND",
पूर्ण;

अटल स्थिर अक्षर *brcmf_fil_get_errstr(u32 err)
अणु
	अगर (err >= ARRAY_SIZE(brcmf_fil_errstr))
		वापस "(unknown)";

	वापस brcmf_fil_errstr[err];
पूर्ण
#अन्यथा
अटल स्थिर अक्षर *brcmf_fil_get_errstr(u32 err)
अणु
	वापस "";
पूर्ण
#पूर्ण_अगर /* DEBUG */

अटल s32
brcmf_fil_cmd_data(काष्ठा brcmf_अगर *अगरp, u32 cmd, व्योम *data, u32 len, bool set)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	s32 err, fwerr;

	अगर (drvr->bus_अगर->state != BRCMF_BUS_UP) अणु
		bphy_err(drvr, "bus is down. we have nothing to do.\n");
		वापस -EIO;
	पूर्ण

	अगर (data != शून्य)
		len = min_t(uपूर्णांक, len, BRCMF_DCMD_MAXLEN);
	अगर (set)
		err = brcmf_proto_set_dcmd(drvr, अगरp->अगरidx, cmd,
					   data, len, &fwerr);
	अन्यथा
		err = brcmf_proto_query_dcmd(drvr, अगरp->अगरidx, cmd,
					     data, len, &fwerr);

	अगर (err) अणु
		brcmf_dbg(FIL, "Failed: error=%d\n", err);
	पूर्ण अन्यथा अगर (fwerr < 0) अणु
		brcmf_dbg(FIL, "Firmware error: %s (%d)\n",
			  brcmf_fil_get_errstr((u32)(-fwerr)), fwerr);
		err = -EBADE;
	पूर्ण
	अगर (अगरp->fwil_fwerr)
		वापस fwerr;

	वापस err;
पूर्ण

s32
brcmf_fil_cmd_data_set(काष्ठा brcmf_अगर *अगरp, u32 cmd, व्योम *data, u32 len)
अणु
	s32 err;

	mutex_lock(&अगरp->drvr->proto_block);

	brcmf_dbg(FIL, "ifidx=%d, cmd=%d, len=%d\n", अगरp->अगरidx, cmd, len);
	brcmf_dbg_hex_dump(BRCMF_FIL_ON(), data,
			   min_t(uपूर्णांक, len, MAX_HEX_DUMP_LEN), "data\n");

	err = brcmf_fil_cmd_data(अगरp, cmd, data, len, true);
	mutex_unlock(&अगरp->drvr->proto_block);

	वापस err;
पूर्ण

s32
brcmf_fil_cmd_data_get(काष्ठा brcmf_अगर *अगरp, u32 cmd, व्योम *data, u32 len)
अणु
	s32 err;

	mutex_lock(&अगरp->drvr->proto_block);
	err = brcmf_fil_cmd_data(अगरp, cmd, data, len, false);

	brcmf_dbg(FIL, "ifidx=%d, cmd=%d, len=%d\n", अगरp->अगरidx, cmd, len);
	brcmf_dbg_hex_dump(BRCMF_FIL_ON(), data,
			   min_t(uपूर्णांक, len, MAX_HEX_DUMP_LEN), "data\n");

	mutex_unlock(&अगरp->drvr->proto_block);

	वापस err;
पूर्ण


s32
brcmf_fil_cmd_पूर्णांक_set(काष्ठा brcmf_अगर *अगरp, u32 cmd, u32 data)
अणु
	s32 err;
	__le32 data_le = cpu_to_le32(data);

	mutex_lock(&अगरp->drvr->proto_block);
	brcmf_dbg(FIL, "ifidx=%d, cmd=%d, value=%d\n", अगरp->अगरidx, cmd, data);
	err = brcmf_fil_cmd_data(अगरp, cmd, &data_le, माप(data_le), true);
	mutex_unlock(&अगरp->drvr->proto_block);

	वापस err;
पूर्ण

s32
brcmf_fil_cmd_पूर्णांक_get(काष्ठा brcmf_अगर *अगरp, u32 cmd, u32 *data)
अणु
	s32 err;
	__le32 data_le = cpu_to_le32(*data);

	mutex_lock(&अगरp->drvr->proto_block);
	err = brcmf_fil_cmd_data(अगरp, cmd, &data_le, माप(data_le), false);
	mutex_unlock(&अगरp->drvr->proto_block);
	*data = le32_to_cpu(data_le);
	brcmf_dbg(FIL, "ifidx=%d, cmd=%d, value=%d\n", अगरp->अगरidx, cmd, *data);

	वापस err;
पूर्ण

अटल u32
brcmf_create_iovar(अक्षर *name, स्थिर अक्षर *data, u32 datalen,
		   अक्षर *buf, u32 buflen)
अणु
	u32 len;

	len = म_माप(name) + 1;

	अगर ((len + datalen) > buflen)
		वापस 0;

	स_नकल(buf, name, len);

	/* append data onto the end of the name string */
	अगर (data && datalen)
		स_नकल(&buf[len], data, datalen);

	वापस len + datalen;
पूर्ण


s32
brcmf_fil_iovar_data_set(काष्ठा brcmf_अगर *अगरp, अक्षर *name, स्थिर व्योम *data,
			 u32 len)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	s32 err;
	u32 buflen;

	mutex_lock(&drvr->proto_block);

	brcmf_dbg(FIL, "ifidx=%d, name=%s, len=%d\n", अगरp->अगरidx, name, len);
	brcmf_dbg_hex_dump(BRCMF_FIL_ON(), data,
			   min_t(uपूर्णांक, len, MAX_HEX_DUMP_LEN), "data\n");

	buflen = brcmf_create_iovar(name, data, len, drvr->proto_buf,
				    माप(drvr->proto_buf));
	अगर (buflen) अणु
		err = brcmf_fil_cmd_data(अगरp, BRCMF_C_SET_VAR, drvr->proto_buf,
					 buflen, true);
	पूर्ण अन्यथा अणु
		err = -EPERM;
		bphy_err(drvr, "Creating iovar failed\n");
	पूर्ण

	mutex_unlock(&drvr->proto_block);
	वापस err;
पूर्ण

s32
brcmf_fil_iovar_data_get(काष्ठा brcmf_अगर *अगरp, अक्षर *name, व्योम *data,
			 u32 len)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	s32 err;
	u32 buflen;

	mutex_lock(&drvr->proto_block);

	buflen = brcmf_create_iovar(name, data, len, drvr->proto_buf,
				    माप(drvr->proto_buf));
	अगर (buflen) अणु
		err = brcmf_fil_cmd_data(अगरp, BRCMF_C_GET_VAR, drvr->proto_buf,
					 buflen, false);
		अगर (err == 0)
			स_नकल(data, drvr->proto_buf, len);
	पूर्ण अन्यथा अणु
		err = -EPERM;
		bphy_err(drvr, "Creating iovar failed\n");
	पूर्ण

	brcmf_dbg(FIL, "ifidx=%d, name=%s, len=%d\n", अगरp->अगरidx, name, len);
	brcmf_dbg_hex_dump(BRCMF_FIL_ON(), data,
			   min_t(uपूर्णांक, len, MAX_HEX_DUMP_LEN), "data\n");

	mutex_unlock(&drvr->proto_block);
	वापस err;
पूर्ण

s32
brcmf_fil_iovar_पूर्णांक_set(काष्ठा brcmf_अगर *अगरp, अक्षर *name, u32 data)
अणु
	__le32 data_le = cpu_to_le32(data);

	वापस brcmf_fil_iovar_data_set(अगरp, name, &data_le, माप(data_le));
पूर्ण

s32
brcmf_fil_iovar_पूर्णांक_get(काष्ठा brcmf_अगर *अगरp, अक्षर *name, u32 *data)
अणु
	__le32 data_le = cpu_to_le32(*data);
	s32 err;

	err = brcmf_fil_iovar_data_get(अगरp, name, &data_le, माप(data_le));
	अगर (err == 0)
		*data = le32_to_cpu(data_le);
	वापस err;
पूर्ण

अटल u32
brcmf_create_bsscfg(s32 bsscfgidx, अक्षर *name, अक्षर *data, u32 datalen,
		    अक्षर *buf, u32 buflen)
अणु
	स्थिर s8 *prefix = "bsscfg:";
	s8 *p;
	u32 prefixlen;
	u32 namelen;
	u32 iolen;
	__le32 bsscfgidx_le;

	अगर (bsscfgidx == 0)
		वापस brcmf_create_iovar(name, data, datalen, buf, buflen);

	prefixlen = म_माप(prefix);
	namelen = म_माप(name) + 1; /* length of iovar  name + null */
	iolen = prefixlen + namelen + माप(bsscfgidx_le) + datalen;

	अगर (buflen < iolen) अणु
		brcmf_err("buffer is too short\n");
		वापस 0;
	पूर्ण

	p = buf;

	/* copy prefix, no null */
	स_नकल(p, prefix, prefixlen);
	p += prefixlen;

	/* copy iovar name including null */
	स_नकल(p, name, namelen);
	p += namelen;

	/* bss config index as first data */
	bsscfgidx_le = cpu_to_le32(bsscfgidx);
	स_नकल(p, &bsscfgidx_le, माप(bsscfgidx_le));
	p += माप(bsscfgidx_le);

	/* parameter buffer follows */
	अगर (datalen)
		स_नकल(p, data, datalen);

	वापस iolen;
पूर्ण

s32
brcmf_fil_bsscfg_data_set(काष्ठा brcmf_अगर *अगरp, अक्षर *name,
			  व्योम *data, u32 len)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	s32 err;
	u32 buflen;

	mutex_lock(&drvr->proto_block);

	brcmf_dbg(FIL, "ifidx=%d, bsscfgidx=%d, name=%s, len=%d\n", अगरp->अगरidx,
		  अगरp->bsscfgidx, name, len);
	brcmf_dbg_hex_dump(BRCMF_FIL_ON(), data,
			   min_t(uपूर्णांक, len, MAX_HEX_DUMP_LEN), "data\n");

	buflen = brcmf_create_bsscfg(अगरp->bsscfgidx, name, data, len,
				     drvr->proto_buf, माप(drvr->proto_buf));
	अगर (buflen) अणु
		err = brcmf_fil_cmd_data(अगरp, BRCMF_C_SET_VAR, drvr->proto_buf,
					 buflen, true);
	पूर्ण अन्यथा अणु
		err = -EPERM;
		bphy_err(drvr, "Creating bsscfg failed\n");
	पूर्ण

	mutex_unlock(&drvr->proto_block);
	वापस err;
पूर्ण

s32
brcmf_fil_bsscfg_data_get(काष्ठा brcmf_अगर *अगरp, अक्षर *name,
			  व्योम *data, u32 len)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	s32 err;
	u32 buflen;

	mutex_lock(&drvr->proto_block);

	buflen = brcmf_create_bsscfg(अगरp->bsscfgidx, name, data, len,
				     drvr->proto_buf, माप(drvr->proto_buf));
	अगर (buflen) अणु
		err = brcmf_fil_cmd_data(अगरp, BRCMF_C_GET_VAR, drvr->proto_buf,
					 buflen, false);
		अगर (err == 0)
			स_नकल(data, drvr->proto_buf, len);
	पूर्ण अन्यथा अणु
		err = -EPERM;
		bphy_err(drvr, "Creating bsscfg failed\n");
	पूर्ण
	brcmf_dbg(FIL, "ifidx=%d, bsscfgidx=%d, name=%s, len=%d\n", अगरp->अगरidx,
		  अगरp->bsscfgidx, name, len);
	brcmf_dbg_hex_dump(BRCMF_FIL_ON(), data,
			   min_t(uपूर्णांक, len, MAX_HEX_DUMP_LEN), "data\n");

	mutex_unlock(&drvr->proto_block);
	वापस err;

पूर्ण

s32
brcmf_fil_bsscfg_पूर्णांक_set(काष्ठा brcmf_अगर *अगरp, अक्षर *name, u32 data)
अणु
	__le32 data_le = cpu_to_le32(data);

	वापस brcmf_fil_bsscfg_data_set(अगरp, name, &data_le,
					 माप(data_le));
पूर्ण

s32
brcmf_fil_bsscfg_पूर्णांक_get(काष्ठा brcmf_अगर *अगरp, अक्षर *name, u32 *data)
अणु
	__le32 data_le = cpu_to_le32(*data);
	s32 err;

	err = brcmf_fil_bsscfg_data_get(अगरp, name, &data_le,
					माप(data_le));
	अगर (err == 0)
		*data = le32_to_cpu(data_le);
	वापस err;
पूर्ण
