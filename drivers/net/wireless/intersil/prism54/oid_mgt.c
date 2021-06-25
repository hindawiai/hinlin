<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2003,2004 Aurelien Alleaume <slts@मुक्त.fr>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>

#समावेश "prismcompat.h"
#समावेश "islpci_dev.h"
#समावेश "islpci_mgt.h"
#समावेश "isl_oid.h"
#समावेश "oid_mgt.h"
#समावेश "isl_ioctl.h"

/* to convert between channel and freq */
अटल स्थिर पूर्णांक frequency_list_bg[] = अणु 2412, 2417, 2422, 2427, 2432,
	2437, 2442, 2447, 2452, 2457, 2462, 2467, 2472, 2484
पूर्ण;

पूर्णांक
channel_of_freq(पूर्णांक f)
अणु
	पूर्णांक c = 0;

	अगर ((f >= 2412) && (f <= 2484)) अणु
		जबतक ((c < 14) && (f != frequency_list_bg[c]))
			c++;
		वापस (c >= 14) ? 0 : ++c;
	पूर्ण अन्यथा अगर ((f >= (पूर्णांक) 5000) && (f <= (पूर्णांक) 6000)) अणु
		वापस ( (f - 5000) / 5 );
	पूर्ण अन्यथा
		वापस 0;
पूर्ण

#घोषणा OID_STRUCT(name,oid,s,t) [name] = अणुoid, 0, माप(s), tपूर्ण
#घोषणा OID_STRUCT_C(name,oid,s,t) OID_STRUCT(name,oid,s,t | OID_FLAG_CACHED)
#घोषणा OID_U32(name,oid) OID_STRUCT(name,oid,u32,OID_TYPE_U32)
#घोषणा OID_U32_C(name,oid) OID_STRUCT_C(name,oid,u32,OID_TYPE_U32)
#घोषणा OID_STRUCT_MLME(name,oid) OID_STRUCT(name,oid,काष्ठा obj_mlme,OID_TYPE_MLME)
#घोषणा OID_STRUCT_MLMEEX(name,oid) OID_STRUCT(name,oid,काष्ठा obj_mlmeex,OID_TYPE_MLMEEX)

#घोषणा OID_UNKNOWN(name,oid) OID_STRUCT(name,oid,0,0)

काष्ठा oid_t isl_oid[] = अणु
	OID_STRUCT(GEN_OID_MACADDRESS, 0x00000000, u8[6], OID_TYPE_ADDR),
	OID_U32(GEN_OID_LINKSTATE, 0x00000001),
	OID_UNKNOWN(GEN_OID_WATCHDOG, 0x00000002),
	OID_UNKNOWN(GEN_OID_MIBOP, 0x00000003),
	OID_UNKNOWN(GEN_OID_OPTIONS, 0x00000004),
	OID_UNKNOWN(GEN_OID_LEDCONFIG, 0x00000005),

	/* 802.11 */
	OID_U32_C(DOT11_OID_BSSTYPE, 0x10000000),
	OID_STRUCT_C(DOT11_OID_BSSID, 0x10000001, u8[6], OID_TYPE_RAW),
	OID_STRUCT_C(DOT11_OID_SSID, 0x10000002, काष्ठा obj_ssid,
		     OID_TYPE_SSID),
	OID_U32(DOT11_OID_STATE, 0x10000003),
	OID_U32(DOT11_OID_AID, 0x10000004),
	OID_STRUCT(DOT11_OID_COUNTRYSTRING, 0x10000005, u8[4], OID_TYPE_RAW),
	OID_STRUCT_C(DOT11_OID_SSIDOVERRIDE, 0x10000006, काष्ठा obj_ssid,
		     OID_TYPE_SSID),

	OID_U32(DOT11_OID_MEDIUMLIMIT, 0x11000000),
	OID_U32_C(DOT11_OID_BEACONPERIOD, 0x11000001),
	OID_U32(DOT11_OID_DTIMPERIOD, 0x11000002),
	OID_U32(DOT11_OID_ATIMWINDOW, 0x11000003),
	OID_U32(DOT11_OID_LISTENINTERVAL, 0x11000004),
	OID_U32(DOT11_OID_CFPPERIOD, 0x11000005),
	OID_U32(DOT11_OID_CFPDURATION, 0x11000006),

	OID_U32_C(DOT11_OID_AUTHENABLE, 0x12000000),
	OID_U32_C(DOT11_OID_PRIVACYINVOKED, 0x12000001),
	OID_U32_C(DOT11_OID_EXUNENCRYPTED, 0x12000002),
	OID_U32_C(DOT11_OID_DEFKEYID, 0x12000003),
	[DOT11_OID_DEFKEYX] = अणु0x12000004, 3, माप (काष्ठा obj_key),
			       OID_FLAG_CACHED | OID_TYPE_KEYपूर्ण,	/* DOT11_OID_DEFKEY1,...DOT11_OID_DEFKEY4 */
	OID_UNKNOWN(DOT11_OID_STAKEY, 0x12000008),
	OID_U32(DOT11_OID_REKEYTHRESHOLD, 0x12000009),
	OID_UNKNOWN(DOT11_OID_STASC, 0x1200000a),

	OID_U32(DOT11_OID_PRIVTXREJECTED, 0x1a000000),
	OID_U32(DOT11_OID_PRIVRXPLAIN, 0x1a000001),
	OID_U32(DOT11_OID_PRIVRXFAILED, 0x1a000002),
	OID_U32(DOT11_OID_PRIVRXNOKEY, 0x1a000003),

	OID_U32_C(DOT11_OID_RTSTHRESH, 0x13000000),
	OID_U32_C(DOT11_OID_FRAGTHRESH, 0x13000001),
	OID_U32_C(DOT11_OID_SHORTRETRIES, 0x13000002),
	OID_U32_C(DOT11_OID_LONGRETRIES, 0x13000003),
	OID_U32_C(DOT11_OID_MAXTXLIFETIME, 0x13000004),
	OID_U32(DOT11_OID_MAXRXLIFETIME, 0x13000005),
	OID_U32(DOT11_OID_AUTHRESPTIMEOUT, 0x13000006),
	OID_U32(DOT11_OID_ASSOCRESPTIMEOUT, 0x13000007),

	OID_UNKNOWN(DOT11_OID_ALOFT_TABLE, 0x1d000000),
	OID_UNKNOWN(DOT11_OID_ALOFT_CTRL_TABLE, 0x1d000001),
	OID_UNKNOWN(DOT11_OID_ALOFT_RETREAT, 0x1d000002),
	OID_UNKNOWN(DOT11_OID_ALOFT_PROGRESS, 0x1d000003),
	OID_U32(DOT11_OID_ALOFT_FIXEDRATE, 0x1d000004),
	OID_UNKNOWN(DOT11_OID_ALOFT_RSSIGRAPH, 0x1d000005),
	OID_UNKNOWN(DOT11_OID_ALOFT_CONFIG, 0x1d000006),

	[DOT11_OID_VDCFX] = अणु0x1b000000, 7, 0, 0पूर्ण,
	OID_U32(DOT11_OID_MAXFRAMEBURST, 0x1b000008),

	OID_U32(DOT11_OID_PSM, 0x14000000),
	OID_U32(DOT11_OID_CAMTIMEOUT, 0x14000001),
	OID_U32(DOT11_OID_RECEIVEDTIMS, 0x14000002),
	OID_U32(DOT11_OID_ROAMPREFERENCE, 0x14000003),

	OID_U32(DOT11_OID_BRIDGELOCAL, 0x15000000),
	OID_U32(DOT11_OID_CLIENTS, 0x15000001),
	OID_U32(DOT11_OID_CLIENTSASSOCIATED, 0x15000002),
	[DOT11_OID_CLIENTX] = अणु0x15000003, 2006, 0, 0पूर्ण,	/* DOT11_OID_CLIENTX,...DOT11_OID_CLIENT2007 */

	OID_STRUCT(DOT11_OID_CLIENTFIND, 0x150007DB, u8[6], OID_TYPE_ADDR),
	OID_STRUCT(DOT11_OID_WDSLINKADD, 0x150007DC, u8[6], OID_TYPE_ADDR),
	OID_STRUCT(DOT11_OID_WDSLINKREMOVE, 0x150007DD, u8[6], OID_TYPE_ADDR),
	OID_STRUCT(DOT11_OID_EAPAUTHSTA, 0x150007DE, u8[6], OID_TYPE_ADDR),
	OID_STRUCT(DOT11_OID_EAPUNAUTHSTA, 0x150007DF, u8[6], OID_TYPE_ADDR),
	OID_U32_C(DOT11_OID_DOT1XENABLE, 0x150007E0),
	OID_UNKNOWN(DOT11_OID_MICFAILURE, 0x150007E1),
	OID_UNKNOWN(DOT11_OID_REKEYINDICATE, 0x150007E2),

	OID_U32(DOT11_OID_MPDUTXSUCCESSFUL, 0x16000000),
	OID_U32(DOT11_OID_MPDUTXONERETRY, 0x16000001),
	OID_U32(DOT11_OID_MPDUTXMULTIPLERETRIES, 0x16000002),
	OID_U32(DOT11_OID_MPDUTXFAILED, 0x16000003),
	OID_U32(DOT11_OID_MPDURXSUCCESSFUL, 0x16000004),
	OID_U32(DOT11_OID_MPDURXDUPS, 0x16000005),
	OID_U32(DOT11_OID_RTSSUCCESSFUL, 0x16000006),
	OID_U32(DOT11_OID_RTSFAILED, 0x16000007),
	OID_U32(DOT11_OID_ACKFAILED, 0x16000008),
	OID_U32(DOT11_OID_FRAMERECEIVES, 0x16000009),
	OID_U32(DOT11_OID_FRAMEERRORS, 0x1600000A),
	OID_U32(DOT11_OID_FRAMEABORTS, 0x1600000B),
	OID_U32(DOT11_OID_FRAMEABORTSPHY, 0x1600000C),

	OID_U32(DOT11_OID_SLOTTIME, 0x17000000),
	OID_U32(DOT11_OID_CWMIN, 0x17000001),
	OID_U32(DOT11_OID_CWMAX, 0x17000002),
	OID_U32(DOT11_OID_ACKWINDOW, 0x17000003),
	OID_U32(DOT11_OID_ANTENNARX, 0x17000004),
	OID_U32(DOT11_OID_ANTENNATX, 0x17000005),
	OID_U32(DOT11_OID_ANTENNADIVERSITY, 0x17000006),
	OID_U32_C(DOT11_OID_CHANNEL, 0x17000007),
	OID_U32_C(DOT11_OID_EDTHRESHOLD, 0x17000008),
	OID_U32(DOT11_OID_PREAMBLESETTINGS, 0x17000009),
	OID_STRUCT(DOT11_OID_RATES, 0x1700000A, u8[IWMAX_BITRATES + 1],
		   OID_TYPE_RAW),
	OID_U32(DOT11_OID_CCAMODESUPPORTED, 0x1700000B),
	OID_U32(DOT11_OID_CCAMODE, 0x1700000C),
	OID_UNKNOWN(DOT11_OID_RSSIVECTOR, 0x1700000D),
	OID_UNKNOWN(DOT11_OID_OUTPUTPOWERTABLE, 0x1700000E),
	OID_U32(DOT11_OID_OUTPUTPOWER, 0x1700000F),
	OID_STRUCT(DOT11_OID_SUPPORTEDRATES, 0x17000010,
		   u8[IWMAX_BITRATES + 1], OID_TYPE_RAW),
	OID_U32_C(DOT11_OID_FREQUENCY, 0x17000011),
	[DOT11_OID_SUPPORTEDFREQUENCIES] =
	    अणु0x17000012, 0, माप (काष्ठा obj_frequencies)
	     + माप (u16) * IWMAX_FREQ, OID_TYPE_FREQUENCIESपूर्ण,

	OID_U32(DOT11_OID_NOISEFLOOR, 0x17000013),
	OID_STRUCT(DOT11_OID_FREQUENCYACTIVITY, 0x17000014, u8[IWMAX_FREQ + 1],
		   OID_TYPE_RAW),
	OID_UNKNOWN(DOT11_OID_IQCALIBRATIONTABLE, 0x17000015),
	OID_U32(DOT11_OID_NONERPPROTECTION, 0x17000016),
	OID_U32(DOT11_OID_SLOTSETTINGS, 0x17000017),
	OID_U32(DOT11_OID_NONERPTIMEOUT, 0x17000018),
	OID_U32(DOT11_OID_PROखाताS, 0x17000019),
	OID_STRUCT(DOT11_OID_EXTENDEDRATES, 0x17000020,
		   u8[IWMAX_BITRATES + 1], OID_TYPE_RAW),

	OID_STRUCT_MLME(DOT11_OID_DEAUTHENTICATE, 0x18000000),
	OID_STRUCT_MLME(DOT11_OID_AUTHENTICATE, 0x18000001),
	OID_STRUCT_MLME(DOT11_OID_DISASSOCIATE, 0x18000002),
	OID_STRUCT_MLME(DOT11_OID_ASSOCIATE, 0x18000003),
	OID_UNKNOWN(DOT11_OID_SCAN, 0x18000004),
	OID_STRUCT_MLMEEX(DOT11_OID_BEACON, 0x18000005),
	OID_STRUCT_MLMEEX(DOT11_OID_PROBE, 0x18000006),
	OID_STRUCT_MLMEEX(DOT11_OID_DEAUTHENTICATEEX, 0x18000007),
	OID_STRUCT_MLMEEX(DOT11_OID_AUTHENTICATEEX, 0x18000008),
	OID_STRUCT_MLMEEX(DOT11_OID_DISASSOCIATEEX, 0x18000009),
	OID_STRUCT_MLMEEX(DOT11_OID_ASSOCIATEEX, 0x1800000A),
	OID_STRUCT_MLMEEX(DOT11_OID_REASSOCIATE, 0x1800000B),
	OID_STRUCT_MLMEEX(DOT11_OID_REASSOCIATEEX, 0x1800000C),

	OID_U32(DOT11_OID_NONERPSTATUS, 0x1E000000),

	OID_U32(DOT11_OID_STATIMEOUT, 0x19000000),
	OID_U32_C(DOT11_OID_MLMEAUTOLEVEL, 0x19000001),
	OID_U32(DOT11_OID_BSSTIMEOUT, 0x19000002),
	[DOT11_OID_ATTACHMENT] = अणु0x19000003, 0,
		माप(काष्ठा obj_attachment), OID_TYPE_ATTACHपूर्ण,
	OID_STRUCT_C(DOT11_OID_PSMBUFFER, 0x19000004, काष्ठा obj_buffer,
		     OID_TYPE_BUFFER),

	OID_U32(DOT11_OID_BSSS, 0x1C000000),
	[DOT11_OID_BSSX] = अणु0x1C000001, 63, माप (काष्ठा obj_bss),
			    OID_TYPE_BSSपूर्ण,	/*DOT11_OID_BSS1,...,DOT11_OID_BSS64 */
	OID_STRUCT(DOT11_OID_BSSFIND, 0x1C000042, काष्ठा obj_bss, OID_TYPE_BSS),
	[DOT11_OID_BSSLIST] = अणु0x1C000043, 0, माप (काष्ठा
						      obj_bsslist) +
			       माप (काष्ठा obj_bss[IWMAX_BSS]),
			       OID_TYPE_BSSLISTपूर्ण,

	OID_UNKNOWN(OID_INL_TUNNEL, 0xFF020000),
	OID_UNKNOWN(OID_INL_MEMADDR, 0xFF020001),
	OID_UNKNOWN(OID_INL_MEMORY, 0xFF020002),
	OID_U32_C(OID_INL_MODE, 0xFF020003),
	OID_UNKNOWN(OID_INL_COMPONENT_NR, 0xFF020004),
	OID_STRUCT(OID_INL_VERSION, 0xFF020005, u8[8], OID_TYPE_RAW),
	OID_UNKNOWN(OID_INL_INTERFACE_ID, 0xFF020006),
	OID_UNKNOWN(OID_INL_COMPONENT_ID, 0xFF020007),
	OID_U32_C(OID_INL_CONFIG, 0xFF020008),
	OID_U32_C(OID_INL_DOT11D_CONFORMANCE, 0xFF02000C),
	OID_U32(OID_INL_PHYCAPABILITIES, 0xFF02000D),
	OID_U32_C(OID_INL_OUTPUTPOWER, 0xFF02000F),

पूर्ण;

पूर्णांक
mgt_init(islpci_निजी *priv)
अणु
	पूर्णांक i;

	priv->mib = kसुस्मृति(OID_NUM_LAST, माप (व्योम *), GFP_KERNEL);
	अगर (!priv->mib)
		वापस -ENOMEM;

	/* Alloc the cache */
	क्रम (i = 0; i < OID_NUM_LAST; i++) अणु
		अगर (isl_oid[i].flags & OID_FLAG_CACHED) अणु
			priv->mib[i] = kसुस्मृति(isl_oid[i].size,
					       (isl_oid[i].range + 1),
					       GFP_KERNEL);
			अगर (!priv->mib[i])
				वापस -ENOMEM;
		पूर्ण अन्यथा
			priv->mib[i] = शून्य;
	पूर्ण

	init_rwsem(&priv->mib_sem);
	prism54_mib_init(priv);

	वापस 0;
पूर्ण

व्योम
mgt_clean(islpci_निजी *priv)
अणु
	पूर्णांक i;

	अगर (!priv->mib)
		वापस;
	क्रम (i = 0; i < OID_NUM_LAST; i++) अणु
		kमुक्त(priv->mib[i]);
		priv->mib[i] = शून्य;
	पूर्ण
	kमुक्त(priv->mib);
	priv->mib = शून्य;
पूर्ण

व्योम
mgt_le_to_cpu(पूर्णांक type, व्योम *data)
अणु
	चयन (type) अणु
	हाल OID_TYPE_U32:
		*(u32 *) data = le32_to_cpu(*(u32 *) data);
		अवरोध;
	हाल OID_TYPE_BUFFER:अणु
			काष्ठा obj_buffer *buff = data;
			buff->size = le32_to_cpu(buff->size);
			buff->addr = le32_to_cpu(buff->addr);
			अवरोध;
		पूर्ण
	हाल OID_TYPE_BSS:अणु
			काष्ठा obj_bss *bss = data;
			bss->age = le16_to_cpu(bss->age);
			bss->channel = le16_to_cpu(bss->channel);
			bss->capinfo = le16_to_cpu(bss->capinfo);
			bss->rates = le16_to_cpu(bss->rates);
			bss->basic_rates = le16_to_cpu(bss->basic_rates);
			अवरोध;
		पूर्ण
	हाल OID_TYPE_BSSLIST:अणु
			काष्ठा obj_bsslist *list = data;
			पूर्णांक i;
			list->nr = le32_to_cpu(list->nr);
			क्रम (i = 0; i < list->nr; i++)
				mgt_le_to_cpu(OID_TYPE_BSS, &list->bsslist[i]);
			अवरोध;
		पूर्ण
	हाल OID_TYPE_FREQUENCIES:अणु
			काष्ठा obj_frequencies *freq = data;
			पूर्णांक i;
			freq->nr = le16_to_cpu(freq->nr);
			क्रम (i = 0; i < freq->nr; i++)
				freq->mhz[i] = le16_to_cpu(freq->mhz[i]);
			अवरोध;
		पूर्ण
	हाल OID_TYPE_MLME:अणु
			काष्ठा obj_mlme *mlme = data;
			mlme->id = le16_to_cpu(mlme->id);
			mlme->state = le16_to_cpu(mlme->state);
			mlme->code = le16_to_cpu(mlme->code);
			अवरोध;
		पूर्ण
	हाल OID_TYPE_MLMEEX:अणु
			काष्ठा obj_mlmeex *mlme = data;
			mlme->id = le16_to_cpu(mlme->id);
			mlme->state = le16_to_cpu(mlme->state);
			mlme->code = le16_to_cpu(mlme->code);
			mlme->size = le16_to_cpu(mlme->size);
			अवरोध;
		पूर्ण
	हाल OID_TYPE_ATTACH:अणु
			काष्ठा obj_attachment *attach = data;
			attach->id = le16_to_cpu(attach->id);
			attach->size = le16_to_cpu(attach->size);
			अवरोध;
	पूर्ण
	हाल OID_TYPE_SSID:
	हाल OID_TYPE_KEY:
	हाल OID_TYPE_ADDR:
	हाल OID_TYPE_RAW:
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल व्योम
mgt_cpu_to_le(पूर्णांक type, व्योम *data)
अणु
	चयन (type) अणु
	हाल OID_TYPE_U32:
		*(u32 *) data = cpu_to_le32(*(u32 *) data);
		अवरोध;
	हाल OID_TYPE_BUFFER:अणु
			काष्ठा obj_buffer *buff = data;
			buff->size = cpu_to_le32(buff->size);
			buff->addr = cpu_to_le32(buff->addr);
			अवरोध;
		पूर्ण
	हाल OID_TYPE_BSS:अणु
			काष्ठा obj_bss *bss = data;
			bss->age = cpu_to_le16(bss->age);
			bss->channel = cpu_to_le16(bss->channel);
			bss->capinfo = cpu_to_le16(bss->capinfo);
			bss->rates = cpu_to_le16(bss->rates);
			bss->basic_rates = cpu_to_le16(bss->basic_rates);
			अवरोध;
		पूर्ण
	हाल OID_TYPE_BSSLIST:अणु
			काष्ठा obj_bsslist *list = data;
			पूर्णांक i;
			list->nr = cpu_to_le32(list->nr);
			क्रम (i = 0; i < list->nr; i++)
				mgt_cpu_to_le(OID_TYPE_BSS, &list->bsslist[i]);
			अवरोध;
		पूर्ण
	हाल OID_TYPE_FREQUENCIES:अणु
			काष्ठा obj_frequencies *freq = data;
			पूर्णांक i;
			freq->nr = cpu_to_le16(freq->nr);
			क्रम (i = 0; i < freq->nr; i++)
				freq->mhz[i] = cpu_to_le16(freq->mhz[i]);
			अवरोध;
		पूर्ण
	हाल OID_TYPE_MLME:अणु
			काष्ठा obj_mlme *mlme = data;
			mlme->id = cpu_to_le16(mlme->id);
			mlme->state = cpu_to_le16(mlme->state);
			mlme->code = cpu_to_le16(mlme->code);
			अवरोध;
		पूर्ण
	हाल OID_TYPE_MLMEEX:अणु
			काष्ठा obj_mlmeex *mlme = data;
			mlme->id = cpu_to_le16(mlme->id);
			mlme->state = cpu_to_le16(mlme->state);
			mlme->code = cpu_to_le16(mlme->code);
			mlme->size = cpu_to_le16(mlme->size);
			अवरोध;
		पूर्ण
	हाल OID_TYPE_ATTACH:अणु
			काष्ठा obj_attachment *attach = data;
			attach->id = cpu_to_le16(attach->id);
			attach->size = cpu_to_le16(attach->size);
			अवरोध;
	पूर्ण
	हाल OID_TYPE_SSID:
	हाल OID_TYPE_KEY:
	हाल OID_TYPE_ADDR:
	हाल OID_TYPE_RAW:
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

/* Note : data is modअगरied during this function */

पूर्णांक
mgt_set_request(islpci_निजी *priv, क्रमागत oid_num_t n, पूर्णांक extra, व्योम *data)
अणु
	पूर्णांक ret = 0;
	काष्ठा islpci_mgmtframe *response = शून्य;
	पूर्णांक response_op = PIMFOR_OP_ERROR;
	पूर्णांक dlen;
	व्योम *cache, *_data = data;
	u32 oid;

	BUG_ON(n >= OID_NUM_LAST);
	BUG_ON(extra > isl_oid[n].range);

	अगर (!priv->mib)
		/* memory has been मुक्तd */
		वापस -1;

	dlen = isl_oid[n].size;
	cache = priv->mib[n];
	cache += (cache ? extra * dlen : 0);
	oid = isl_oid[n].oid + extra;

	अगर (_data == शून्य)
		/* we are requested to re-set a cached value */
		_data = cache;
	अन्यथा
		mgt_cpu_to_le(isl_oid[n].flags & OID_FLAG_TYPE, _data);
	/* If we are going to ग_लिखो to the cache, we करोn't want anyone to पढ़ो
	 * it -> acquire ग_लिखो lock.
	 * Else we could acquire a पढ़ो lock to be sure we करोn't bother the
	 * commit process (which takes a ग_लिखो lock). But I'm not sure if it's
	 * needed.
	 */
	अगर (cache)
		करोwn_ग_लिखो(&priv->mib_sem);

	अगर (islpci_get_state(priv) >= PRV_STATE_READY) अणु
		ret = islpci_mgt_transaction(priv->ndev, PIMFOR_OP_SET, oid,
					     _data, dlen, &response);
		अगर (!ret) अणु
			response_op = response->header->operation;
			islpci_mgt_release(response);
		पूर्ण
		अगर (ret || response_op == PIMFOR_OP_ERROR)
			ret = -EIO;
	पूर्ण अन्यथा अगर (!cache)
		ret = -EIO;

	अगर (cache) अणु
		अगर (!ret && data)
			स_नकल(cache, _data, dlen);
		up_ग_लिखो(&priv->mib_sem);
	पूर्ण

	/* re-set given data to what it was */
	अगर (data)
		mgt_le_to_cpu(isl_oid[n].flags & OID_FLAG_TYPE, data);

	वापस ret;
पूर्ण

/* None of these are cached */
पूर्णांक
mgt_set_varlen(islpci_निजी *priv, क्रमागत oid_num_t n, व्योम *data, पूर्णांक extra_len)
अणु
	पूर्णांक ret = 0;
	काष्ठा islpci_mgmtframe *response;
	पूर्णांक response_op = PIMFOR_OP_ERROR;
	पूर्णांक dlen;
	u32 oid;

	BUG_ON(n >= OID_NUM_LAST);

	dlen = isl_oid[n].size;
	oid = isl_oid[n].oid;

	mgt_cpu_to_le(isl_oid[n].flags & OID_FLAG_TYPE, data);

	अगर (islpci_get_state(priv) >= PRV_STATE_READY) अणु
		ret = islpci_mgt_transaction(priv->ndev, PIMFOR_OP_SET, oid,
					     data, dlen + extra_len, &response);
		अगर (!ret) अणु
			response_op = response->header->operation;
			islpci_mgt_release(response);
		पूर्ण
		अगर (ret || response_op == PIMFOR_OP_ERROR)
			ret = -EIO;
	पूर्ण अन्यथा
		ret = -EIO;

	/* re-set given data to what it was */
	अगर (data)
		mgt_le_to_cpu(isl_oid[n].flags & OID_FLAG_TYPE, data);

	वापस ret;
पूर्ण

पूर्णांक
mgt_get_request(islpci_निजी *priv, क्रमागत oid_num_t n, पूर्णांक extra, व्योम *data,
		जोड़ oid_res_t *res)
अणु

	पूर्णांक ret = -EIO;
	पूर्णांक reslen = 0;
	काष्ठा islpci_mgmtframe *response = शून्य;

	पूर्णांक dlen;
	व्योम *cache, *_res = शून्य;
	u32 oid;

	BUG_ON(n >= OID_NUM_LAST);
	BUG_ON(extra > isl_oid[n].range);

	res->ptr = शून्य;

	अगर (!priv->mib)
		/* memory has been मुक्तd */
		वापस -1;

	dlen = isl_oid[n].size;
	cache = priv->mib[n];
	cache += cache ? extra * dlen : 0;
	oid = isl_oid[n].oid + extra;
	reslen = dlen;

	अगर (cache)
		करोwn_पढ़ो(&priv->mib_sem);

	अगर (islpci_get_state(priv) >= PRV_STATE_READY) अणु
		ret = islpci_mgt_transaction(priv->ndev, PIMFOR_OP_GET,
					     oid, data, dlen, &response);
		अगर (ret || !response ||
		    response->header->operation == PIMFOR_OP_ERROR) अणु
			अगर (response)
				islpci_mgt_release(response);
			ret = -EIO;
		पूर्ण
		अगर (!ret) अणु
			_res = response->data;
			reslen = response->header->length;
		पूर्ण
	पूर्ण अन्यथा अगर (cache) अणु
		_res = cache;
		ret = 0;
	पूर्ण
	अगर ((isl_oid[n].flags & OID_FLAG_TYPE) == OID_TYPE_U32)
		res->u = ret ? 0 : le32_to_cpu(*(u32 *) _res);
	अन्यथा अणु
		res->ptr = kदो_स्मृति(reslen, GFP_KERNEL);
		BUG_ON(res->ptr == शून्य);
		अगर (ret)
			स_रखो(res->ptr, 0, reslen);
		अन्यथा अणु
			स_नकल(res->ptr, _res, reslen);
			mgt_le_to_cpu(isl_oid[n].flags & OID_FLAG_TYPE,
				      res->ptr);
		पूर्ण
	पूर्ण
	अगर (cache)
		up_पढ़ो(&priv->mib_sem);

	अगर (response && !ret)
		islpci_mgt_release(response);

	अगर (reslen > isl_oid[n].size)
		prपूर्णांकk(KERN_DEBUG
		       "mgt_get_request(0x%x): received data length was bigger "
		       "than expected (%d > %d). Memory is probably corrupted...",
		       oid, reslen, isl_oid[n].size);

	वापस ret;
पूर्ण

/* lock outside */
पूर्णांक
mgt_commit_list(islpci_निजी *priv, क्रमागत oid_num_t *l, पूर्णांक n)
अणु
	पूर्णांक i, ret = 0;
	काष्ठा islpci_mgmtframe *response;

	क्रम (i = 0; i < n; i++) अणु
		काष्ठा oid_t *t = &(isl_oid[l[i]]);
		व्योम *data = priv->mib[l[i]];
		पूर्णांक j = 0;
		u32 oid = t->oid;
		BUG_ON(data == शून्य);
		जबतक (j <= t->range) अणु
			पूर्णांक r = islpci_mgt_transaction(priv->ndev, PIMFOR_OP_SET,
						      oid, data, t->size,
						      &response);
			अगर (response) अणु
				r |= (response->header->operation == PIMFOR_OP_ERROR);
				islpci_mgt_release(response);
			पूर्ण
			अगर (r)
				prपूर्णांकk(KERN_ERR "%s: mgt_commit_list: failure. "
					"oid=%08x err=%d\n",
					priv->ndev->name, oid, r);
			ret |= r;
			j++;
			oid++;
			data += t->size;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/* Lock outside */

व्योम
mgt_set(islpci_निजी *priv, क्रमागत oid_num_t n, व्योम *data)
अणु
	BUG_ON(n >= OID_NUM_LAST);
	BUG_ON(priv->mib[n] == शून्य);

	स_नकल(priv->mib[n], data, isl_oid[n].size);
	mgt_cpu_to_le(isl_oid[n].flags & OID_FLAG_TYPE, priv->mib[n]);
पूर्ण

व्योम
mgt_get(islpci_निजी *priv, क्रमागत oid_num_t n, व्योम *res)
अणु
	BUG_ON(n >= OID_NUM_LAST);
	BUG_ON(priv->mib[n] == शून्य);
	BUG_ON(res == शून्य);

	स_नकल(res, priv->mib[n], isl_oid[n].size);
	mgt_le_to_cpu(isl_oid[n].flags & OID_FLAG_TYPE, res);
पूर्ण

/* Commits the cache. Lock outside. */

अटल क्रमागत oid_num_t commit_part1[] = अणु
	OID_INL_CONFIG,
	OID_INL_MODE,
	DOT11_OID_BSSTYPE,
	DOT11_OID_CHANNEL,
	DOT11_OID_MLMEAUTOLEVEL
पूर्ण;

अटल क्रमागत oid_num_t commit_part2[] = अणु
	DOT11_OID_SSID,
	DOT11_OID_PSMBUFFER,
	DOT11_OID_AUTHENABLE,
	DOT11_OID_PRIVACYINVOKED,
	DOT11_OID_EXUNENCRYPTED,
	DOT11_OID_DEFKEYX,	/* MULTIPLE */
	DOT11_OID_DEFKEYID,
	DOT11_OID_DOT1XENABLE,
	OID_INL_DOT11D_CONFORMANCE,
	/* Do not initialize this - fw < 1.0.4.3 rejects it
	OID_INL_OUTPUTPOWER,
	*/
पूर्ण;

/* update the MAC addr. */
अटल पूर्णांक
mgt_update_addr(islpci_निजी *priv)
अणु
	काष्ठा islpci_mgmtframe *res;
	पूर्णांक ret;

	ret = islpci_mgt_transaction(priv->ndev, PIMFOR_OP_GET,
				     isl_oid[GEN_OID_MACADDRESS].oid, शून्य,
				     isl_oid[GEN_OID_MACADDRESS].size, &res);

	अगर ((ret == 0) && res && (res->header->operation != PIMFOR_OP_ERROR))
		स_नकल(priv->ndev->dev_addr, res->data, ETH_ALEN);
	अन्यथा
		ret = -EIO;
	अगर (res)
		islpci_mgt_release(res);

	अगर (ret)
		prपूर्णांकk(KERN_ERR "%s: mgt_update_addr: failure\n", priv->ndev->name);
	वापस ret;
पूर्ण

पूर्णांक
mgt_commit(islpci_निजी *priv)
अणु
	पूर्णांक rvalue;
	क्रमागत oid_num_t u;

	अगर (islpci_get_state(priv) < PRV_STATE_INIT)
		वापस 0;

	rvalue = mgt_commit_list(priv, commit_part1, ARRAY_SIZE(commit_part1));

	अगर (priv->iw_mode != IW_MODE_MONITOR)
		rvalue |= mgt_commit_list(priv, commit_part2, ARRAY_SIZE(commit_part2));

	u = OID_INL_MODE;
	rvalue |= mgt_commit_list(priv, &u, 1);
	rvalue |= mgt_update_addr(priv);

	अगर (rvalue) अणु
		/* some request have failed. The device might be in an
		   incoherent state. We should reset it ! */
		prपूर्णांकk(KERN_DEBUG "%s: mgt_commit: failure\n", priv->ndev->name);
	पूर्ण
	वापस rvalue;
पूर्ण

/* The following OIDs need to be "unlatched":
 *
 * MEDIUMLIMIT,BEACONPERIOD,DTIMPERIOD,ATIMWINDOW,LISTENINTERVAL
 * FREQUENCY,EXTENDEDRATES.
 *
 * The way to करो this is to set ESSID. Note though that they may get
 * unlatch beक्रमe though by setting another OID. */
#अगर 0
व्योम
mgt_unlatch_all(islpci_निजी *priv)
अणु
	u32 u;
	पूर्णांक rvalue = 0;

	अगर (islpci_get_state(priv) < PRV_STATE_INIT)
		वापस;

	u = DOT11_OID_SSID;
	rvalue = mgt_commit_list(priv, &u, 1);
	/* Necessary अगर in MANUAL RUN mode? */
#अगर 0
	u = OID_INL_MODE;
	rvalue |= mgt_commit_list(priv, &u, 1);

	u = DOT11_OID_MLMEAUTOLEVEL;
	rvalue |= mgt_commit_list(priv, &u, 1);

	u = OID_INL_MODE;
	rvalue |= mgt_commit_list(priv, &u, 1);
#पूर्ण_अगर

	अगर (rvalue)
		prपूर्णांकk(KERN_DEBUG "%s: Unlatching OIDs failed\n", priv->ndev->name);
पूर्ण
#पूर्ण_अगर

/* This will tell you अगर you are allowed to answer a mlme(ex) request .*/

पूर्णांक
mgt_mlme_answer(islpci_निजी *priv)
अणु
	u32 mlmeस्वतःlevel;
	/* Acquire a पढ़ो lock because अगर we are in a mode change, it's
	 * possible to answer true, जबतक the card is leaving master to managed
	 * mode. Answering to a mlme in this situation could hang the card.
	 */
	करोwn_पढ़ो(&priv->mib_sem);
	mlmeस्वतःlevel =
	    le32_to_cpu(*(u32 *) priv->mib[DOT11_OID_MLMEAUTOLEVEL]);
	up_पढ़ो(&priv->mib_sem);

	वापस ((priv->iw_mode == IW_MODE_MASTER) &&
		(mlmeस्वतःlevel >= DOT11_MLME_INTERMEDIATE));
पूर्ण

क्रमागत oid_num_t
mgt_oidtonum(u32 oid)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < OID_NUM_LAST; i++)
		अगर (isl_oid[i].oid == oid)
			वापस i;

	prपूर्णांकk(KERN_DEBUG "looking for an unknown oid 0x%x", oid);

	वापस OID_NUM_LAST;
पूर्ण

पूर्णांक
mgt_response_to_str(क्रमागत oid_num_t n, जोड़ oid_res_t *r, अक्षर *str)
अणु
	चयन (isl_oid[n].flags & OID_FLAG_TYPE) अणु
	हाल OID_TYPE_U32:
		वापस scnम_लिखो(str, PRIV_STR_SIZE, "%u\n", r->u);
	हाल OID_TYPE_BUFFER:अणु
			काष्ठा obj_buffer *buff = r->ptr;
			वापस scnम_लिखो(str, PRIV_STR_SIZE,
					"size=%u\naddr=0x%X\n", buff->size,
					buff->addr);
		पूर्ण
		अवरोध;
	हाल OID_TYPE_BSS:अणु
			काष्ठा obj_bss *bss = r->ptr;
			वापस scnम_लिखो(str, PRIV_STR_SIZE,
					"age=%u\nchannel=%u\n"
					"capinfo=0x%X\nrates=0x%X\n"
					"basic_rates=0x%X\n", bss->age,
					bss->channel, bss->capinfo,
					bss->rates, bss->basic_rates);
		पूर्ण
		अवरोध;
	हाल OID_TYPE_BSSLIST:अणु
			काष्ठा obj_bsslist *list = r->ptr;
			पूर्णांक i, k;
			k = scnम_लिखो(str, PRIV_STR_SIZE, "nr=%u\n", list->nr);
			क्रम (i = 0; i < list->nr; i++)
				k += scnम_लिखो(str + k, PRIV_STR_SIZE - k,
					      "bss[%u] :\nage=%u\nchannel=%u\n"
					      "capinfo=0x%X\nrates=0x%X\n"
					      "basic_rates=0x%X\n",
					      i, list->bsslist[i].age,
					      list->bsslist[i].channel,
					      list->bsslist[i].capinfo,
					      list->bsslist[i].rates,
					      list->bsslist[i].basic_rates);
			वापस k;
		पूर्ण
		अवरोध;
	हाल OID_TYPE_FREQUENCIES:अणु
			काष्ठा obj_frequencies *freq = r->ptr;
			पूर्णांक i, t;
			prपूर्णांकk("nr : %u\n", freq->nr);
			t = scnम_लिखो(str, PRIV_STR_SIZE, "nr=%u\n", freq->nr);
			क्रम (i = 0; i < freq->nr; i++)
				t += scnम_लिखो(str + t, PRIV_STR_SIZE - t,
					      "mhz[%u]=%u\n", i, freq->mhz[i]);
			वापस t;
		पूर्ण
		अवरोध;
	हाल OID_TYPE_MLME:अणु
			काष्ठा obj_mlme *mlme = r->ptr;
			वापस scnम_लिखो(str, PRIV_STR_SIZE,
					"id=0x%X\nstate=0x%X\ncode=0x%X\n",
					mlme->id, mlme->state, mlme->code);
		पूर्ण
		अवरोध;
	हाल OID_TYPE_MLMEEX:अणु
			काष्ठा obj_mlmeex *mlme = r->ptr;
			वापस scnम_लिखो(str, PRIV_STR_SIZE,
					"id=0x%X\nstate=0x%X\n"
					"code=0x%X\nsize=0x%X\n", mlme->id,
					mlme->state, mlme->code, mlme->size);
		पूर्ण
		अवरोध;
	हाल OID_TYPE_ATTACH:अणु
			काष्ठा obj_attachment *attach = r->ptr;
			वापस scnम_लिखो(str, PRIV_STR_SIZE,
					"id=%d\nsize=%d\n",
					attach->id,
					attach->size);
		पूर्ण
		अवरोध;
	हाल OID_TYPE_SSID:अणु
			काष्ठा obj_ssid *ssid = r->ptr;
			वापस scnम_लिखो(str, PRIV_STR_SIZE,
					"length=%u\noctets=%.*s\n",
					ssid->length, ssid->length,
					ssid->octets);
		पूर्ण
		अवरोध;
	हाल OID_TYPE_KEY:अणु
			काष्ठा obj_key *key = r->ptr;
			पूर्णांक t, i;
			t = scnम_लिखो(str, PRIV_STR_SIZE,
				     "type=0x%X\nlength=0x%X\nkey=0x",
				     key->type, key->length);
			क्रम (i = 0; i < key->length; i++)
				t += scnम_लिखो(str + t, PRIV_STR_SIZE - t,
					      "%02X:", key->key[i]);
			t += scnम_लिखो(str + t, PRIV_STR_SIZE - t, "\n");
			वापस t;
		पूर्ण
		अवरोध;
	हाल OID_TYPE_RAW:
	हाल OID_TYPE_ADDR:अणु
			अचिन्हित अक्षर *buff = r->ptr;
			पूर्णांक t, i;
			t = scnम_लिखो(str, PRIV_STR_SIZE, "hex data=");
			क्रम (i = 0; i < isl_oid[n].size; i++)
				t += scnम_लिखो(str + t, PRIV_STR_SIZE - t,
					      "%02X:", buff[i]);
			t += scnम_लिखो(str + t, PRIV_STR_SIZE - t, "\n");
			वापस t;
		पूर्ण
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	वापस 0;
पूर्ण
