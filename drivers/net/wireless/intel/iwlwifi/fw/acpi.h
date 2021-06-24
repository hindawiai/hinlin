<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2017 Intel Deutschland GmbH
 * Copyright (C) 2018-2021 Intel Corporation
 */
#अगर_अघोषित __iwl_fw_acpi__
#घोषणा __iwl_fw_acpi__

#समावेश <linux/acpi.h>
#समावेश "fw/api/commands.h"
#समावेश "fw/api/power.h"
#समावेश "fw/api/phy.h"
#समावेश "fw/api/nvm-reg.h"
#समावेश "fw/img.h"
#समावेश "iwl-trans.h"


#घोषणा ACPI_WRDS_METHOD	"WRDS"
#घोषणा ACPI_EWRD_METHOD	"EWRD"
#घोषणा ACPI_WGDS_METHOD	"WGDS"
#घोषणा ACPI_WRDD_METHOD	"WRDD"
#घोषणा ACPI_SPLC_METHOD	"SPLC"
#घोषणा ACPI_ECKV_METHOD	"ECKV"
#घोषणा ACPI_PPAG_METHOD	"PPAG"
#घोषणा ACPI_WTAS_METHOD	"WTAS"

#घोषणा ACPI_WIFI_DOMAIN	(0x07)

#घोषणा ACPI_SAR_TABLE_SIZE		10
#घोषणा ACPI_SAR_PROखाता_NUM		4

#घोषणा ACPI_GEO_TABLE_SIZE		6
#घोषणा ACPI_NUM_GEO_PROखाताS		3
#घोषणा ACPI_GEO_PER_CHAIN_SIZE		3

#घोषणा ACPI_SAR_NUM_CHAIN_LIMITS	2
#घोषणा ACPI_SAR_NUM_SUB_BANDS		5
#घोषणा ACPI_SAR_NUM_TABLES		1

#घोषणा ACPI_WRDS_WIFI_DATA_SIZE	(ACPI_SAR_TABLE_SIZE + 2)
#घोषणा ACPI_EWRD_WIFI_DATA_SIZE	((ACPI_SAR_PROखाता_NUM - 1) * \
					 ACPI_SAR_TABLE_SIZE + 3)
#घोषणा ACPI_WGDS_WIFI_DATA_SIZE	19
#घोषणा ACPI_WRDD_WIFI_DATA_SIZE	2
#घोषणा ACPI_SPLC_WIFI_DATA_SIZE	2
#घोषणा ACPI_ECKV_WIFI_DATA_SIZE	2

/*
 * 1 type, 1 enabled, 1 block list size, 16 block list array
 */
#घोषणा APCI_WTAS_BLACK_LIST_MAX	16
#घोषणा ACPI_WTAS_WIFI_DATA_SIZE	(3 + APCI_WTAS_BLACK_LIST_MAX)

#घोषणा ACPI_WGDS_TABLE_SIZE		3

#घोषणा ACPI_PPAG_WIFI_DATA_SIZE_V1	((IWL_NUM_CHAIN_LIMITS * \
					  IWL_NUM_SUB_BANDS_V1) + 2)
#घोषणा ACPI_PPAG_WIFI_DATA_SIZE_V2	((IWL_NUM_CHAIN_LIMITS * \
					  IWL_NUM_SUB_BANDS_V2) + 2)

/* PPAG gain value bounds in 1/8 dBm */
#घोषणा ACPI_PPAG_MIN_LB -16
#घोषणा ACPI_PPAG_MAX_LB 24
#घोषणा ACPI_PPAG_MIN_HB -16
#घोषणा ACPI_PPAG_MAX_HB 40

काष्ठा iwl_sar_profile अणु
	bool enabled;
	u8 table[ACPI_SAR_TABLE_SIZE];
पूर्ण;

काष्ठा iwl_geo_profile अणु
	u8 values[ACPI_GEO_TABLE_SIZE];
पूर्ण;

क्रमागत iwl_dsm_funcs_rev_0 अणु
	DSM_FUNC_QUERY = 0,
	DSM_FUNC_DISABLE_SRD = 1,
	DSM_FUNC_ENABLE_INDONESIA_5G2 = 2,
	DSM_FUNC_11AX_ENABLEMENT = 6,
पूर्ण;

क्रमागत iwl_dsm_values_srd अणु
	DSM_VALUE_SRD_ACTIVE,
	DSM_VALUE_SRD_PASSIVE,
	DSM_VALUE_SRD_DISABLE,
	DSM_VALUE_SRD_MAX
पूर्ण;

क्रमागत iwl_dsm_values_inकरोnesia अणु
	DSM_VALUE_INDONESIA_DISABLE,
	DSM_VALUE_INDONESIA_ENABLE,
	DSM_VALUE_INDONESIA_RESERVED,
	DSM_VALUE_INDONESIA_MAX
पूर्ण;

/* DSM RFI uses a dअगरferent GUID, so need separate definitions */

#घोषणा DSM_RFI_FUNC_ENABLE 3

क्रमागत iwl_dsm_values_rfi अणु
	DSM_VALUE_RFI_ENABLE,
	DSM_VALUE_RFI_DISABLE,
	DSM_VALUE_RFI_MAX
पूर्ण;

#अगर_घोषित CONFIG_ACPI

काष्ठा iwl_fw_runसमय;

बाह्य स्थिर guid_t iwl_guid;
बाह्य स्थिर guid_t iwl_rfi_guid;

व्योम *iwl_acpi_get_object(काष्ठा device *dev, acpi_string method);

पूर्णांक iwl_acpi_get_dsm_u8(काष्ठा device *dev, पूर्णांक rev, पूर्णांक func,
			स्थिर guid_t *guid, u8 *value);

जोड़ acpi_object *iwl_acpi_get_wअगरi_pkg(काष्ठा device *dev,
					 जोड़ acpi_object *data,
					 पूर्णांक data_size, पूर्णांक *tbl_rev);

/**
 * iwl_acpi_get_mcc - पढ़ो MCC from ACPI, अगर available
 *
 * @dev: the काष्ठा device
 * @mcc: output buffer (3 bytes) that will get the MCC
 *
 * This function tries to पढ़ो the current MCC from ACPI अगर available.
 */
पूर्णांक iwl_acpi_get_mcc(काष्ठा device *dev, अक्षर *mcc);

u64 iwl_acpi_get_pwr_limit(काष्ठा device *dev);

/*
 * iwl_acpi_get_eckv - पढ़ो बाह्यal घड़ी validation from ACPI, अगर available
 *
 * @dev: the काष्ठा device
 * @extl_clk: output var (2 bytes) that will get the clk indication.
 *
 * This function tries to पढ़ो the बाह्यal घड़ी indication
 * from ACPI अगर available.
 */
पूर्णांक iwl_acpi_get_eckv(काष्ठा device *dev, u32 *extl_clk);

पूर्णांक iwl_sar_select_profile(काष्ठा iwl_fw_runसमय *fwrt,
			   __le16 *per_chain, u32 n_tables, u32 n_subbands,
			   पूर्णांक prof_a, पूर्णांक prof_b);

पूर्णांक iwl_sar_get_wrds_table(काष्ठा iwl_fw_runसमय *fwrt);

पूर्णांक iwl_sar_get_ewrd_table(काष्ठा iwl_fw_runसमय *fwrt);

पूर्णांक iwl_sar_get_wgds_table(काष्ठा iwl_fw_runसमय *fwrt);

bool iwl_sar_geo_support(काष्ठा iwl_fw_runसमय *fwrt);

पूर्णांक iwl_sar_geo_init(काष्ठा iwl_fw_runसमय *fwrt,
		     काष्ठा iwl_per_chain_offset *table, u32 n_bands);

पूर्णांक iwl_acpi_get_tas(काष्ठा iwl_fw_runसमय *fwrt, __le32 *block_list_array,
		     पूर्णांक *block_list_size);

__le32 iwl_acpi_get_lari_config_biपंचांगap(काष्ठा iwl_fw_runसमय *fwrt);

#अन्यथा /* CONFIG_ACPI */

अटल अंतरभूत व्योम *iwl_acpi_get_object(काष्ठा device *dev, acpi_string method)
अणु
	वापस ERR_PTR(-ENOENT);
पूर्ण

अटल अंतरभूत व्योम *iwl_acpi_get_dsm_object(काष्ठा device *dev, पूर्णांक rev,
					    पूर्णांक func, जोड़ acpi_object *args)
अणु
	वापस ERR_PTR(-ENOENT);
पूर्ण

अटल अंतरभूत पूर्णांक iwl_acpi_get_dsm_u8(काष्ठा device *dev, पूर्णांक rev, पूर्णांक func,
				      स्थिर guid_t *guid, u8 *value)
अणु
	वापस -ENOENT;
पूर्ण

अटल अंतरभूत जोड़ acpi_object *iwl_acpi_get_wअगरi_pkg(काष्ठा device *dev,
						       जोड़ acpi_object *data,
						       पूर्णांक data_size,
						       पूर्णांक *tbl_rev)
अणु
	वापस ERR_PTR(-ENOENT);
पूर्ण

अटल अंतरभूत पूर्णांक iwl_acpi_get_mcc(काष्ठा device *dev, अक्षर *mcc)
अणु
	वापस -ENOENT;
पूर्ण

अटल अंतरभूत u64 iwl_acpi_get_pwr_limit(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक iwl_acpi_get_eckv(काष्ठा device *dev, u32 *extl_clk)
अणु
	वापस -ENOENT;
पूर्ण

अटल अंतरभूत पूर्णांक iwl_sar_select_profile(काष्ठा iwl_fw_runसमय *fwrt,
			   __le16 *per_chain, u32 n_tables, u32 n_subbands,
			   पूर्णांक prof_a, पूर्णांक prof_b)
अणु
	वापस -ENOENT;
पूर्ण

अटल अंतरभूत पूर्णांक iwl_sar_get_wrds_table(काष्ठा iwl_fw_runसमय *fwrt)
अणु
	वापस -ENOENT;
पूर्ण

अटल अंतरभूत पूर्णांक iwl_sar_get_ewrd_table(काष्ठा iwl_fw_runसमय *fwrt)
अणु
	वापस -ENOENT;
पूर्ण

अटल अंतरभूत पूर्णांक iwl_sar_get_wgds_table(काष्ठा iwl_fw_runसमय *fwrt)
अणु
	वापस -ENOENT;
पूर्ण

अटल अंतरभूत bool iwl_sar_geo_support(काष्ठा iwl_fw_runसमय *fwrt)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक iwl_acpi_get_tas(काष्ठा iwl_fw_runसमय *fwrt,
				   __le32 *block_list_array,
				   पूर्णांक *block_list_size)
अणु
	वापस -ENOENT;
पूर्ण

अटल अंतरभूत __le32 iwl_acpi_get_lari_config_biपंचांगap(काष्ठा iwl_fw_runसमय *fwrt)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_ACPI */
#पूर्ण_अगर /* __iwl_fw_acpi__ */
