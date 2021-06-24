<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright(c) 2013-2015 Intel Corporation. All rights reserved.
 */
#अगर_अघोषित __LABEL_H__
#घोषणा __LABEL_H__

#समावेश <linux/ndctl.h>
#समावेश <linux/sizes.h>
#समावेश <linux/uuid.h>
#समावेश <linux/पन.स>

क्रमागत अणु
	NSINDEX_SIG_LEN = 16,
	NSINDEX_ALIGN = 256,
	NSINDEX_SEQ_MASK = 0x3,
	NSLABEL_UUID_LEN = 16,
	NSLABEL_NAME_LEN = 64,
	NSLABEL_FLAG_ROLABEL = 0x1,  /* पढ़ो-only label */
	NSLABEL_FLAG_LOCAL = 0x2,    /* DIMM-local namespace */
	NSLABEL_FLAG_BTT = 0x4,      /* namespace contains a BTT */
	NSLABEL_FLAG_UPDATING = 0x8, /* label being updated */
	BTT_ALIGN = 4096,            /* all btt काष्ठाures */
	BTTINFO_SIG_LEN = 16,
	BTTINFO_UUID_LEN = 16,
	BTTINFO_FLAG_ERROR = 0x1,    /* error state (पढ़ो-only) */
	BTTINFO_MAJOR_VERSION = 1,
	ND_LABEL_MIN_SIZE = 256 * 4, /* see माप_namespace_index() */
	ND_LABEL_ID_SIZE = 50,
	ND_NSINDEX_INIT = 0x1,
पूर्ण;

/**
 * काष्ठा nd_namespace_index - label set superblock
 * @sig: NAMESPACE_INDEX\0
 * @flags: placeholder
 * @seq: sequence number क्रम this index
 * @myoff: offset of this index in label area
 * @mysize: size of this index काष्ठा
 * @otheroff: offset of other index
 * @labeloff: offset of first label slot
 * @nslot: total number of label slots
 * @major: label area major version
 * @minor: label area minor version
 * @checksum: fletcher64 of all fields
 * @मुक्त[0]: biपंचांगap, nlabel bits
 *
 * The size of मुक्त[] is rounded up so the total काष्ठा size is a
 * multiple of NSINDEX_ALIGN bytes.  Any bits this allocates beyond
 * nlabel bits must be zero.
 */
काष्ठा nd_namespace_index अणु
	u8 sig[NSINDEX_SIG_LEN];
	u8 flags[3];
	u8 labelsize;
	__le32 seq;
	__le64 myoff;
	__le64 mysize;
	__le64 otheroff;
	__le64 labeloff;
	__le32 nslot;
	__le16 major;
	__le16 minor;
	__le64 checksum;
	u8 मुक्त[];
पूर्ण;

/**
 * काष्ठा nd_namespace_label - namespace superblock
 * @uuid: UUID per RFC 4122
 * @name: optional name (शून्य-terminated)
 * @flags: see NSLABEL_FLAG_*
 * @nlabel: num labels to describe this ns
 * @position: labels position in set
 * @isetcookie: पूर्णांकerleave set cookie
 * @lbasize: LBA size in bytes or 0 क्रम pmem
 * @dpa: DPA of NVM range on this DIMM
 * @rawsize: size of namespace
 * @slot: slot of this label in label area
 * @unused: must be zero
 */
काष्ठा nd_namespace_label अणु
	u8 uuid[NSLABEL_UUID_LEN];
	u8 name[NSLABEL_NAME_LEN];
	__le32 flags;
	__le16 nlabel;
	__le16 position;
	__le64 isetcookie;
	__le64 lbasize;
	__le64 dpa;
	__le64 rawsize;
	__le32 slot;
	/*
	 * Accessing fields past this poपूर्णांक should be gated by a
	 * namespace_label_has() check.
	 */
	u8 align;
	u8 reserved[3];
	guid_t type_guid;
	guid_t असलtraction_guid;
	u8 reserved2[88];
	__le64 checksum;
पूर्ण;

#घोषणा NVDIMM_BTT_GUID "8aed63a2-29a2-4c66-8b12-f05d15d3922a"
#घोषणा NVDIMM_BTT2_GUID "18633bfc-1735-4217-8ac9-17239282d3f8"
#घोषणा NVDIMM_PFN_GUID "266400ba-fb9f-4677-bcb0-968f11d0d225"
#घोषणा NVDIMM_DAX_GUID "97a86d9c-3cdd-4eda-986f-5068b4f80088"

/**
 * काष्ठा nd_label_id - identअगरier string क्रम dpa allocation
 * @id: "{blk|pmem}-<namespace uuid>"
 */
काष्ठा nd_label_id अणु
	अक्षर id[ND_LABEL_ID_SIZE];
पूर्ण;

/*
 * If the 'best' index is invalid, so is the 'next' index.  Otherwise,
 * the next index is MOD(index+1, 2)
 */
अटल अंतरभूत पूर्णांक nd_label_next_nsindex(पूर्णांक index)
अणु
	अगर (index < 0)
		वापस -1;

	वापस (index + 1) % 2;
पूर्ण

काष्ठा nvdimm_drvdata;
पूर्णांक nd_label_data_init(काष्ठा nvdimm_drvdata *ndd);
माप_प्रकार माप_namespace_index(काष्ठा nvdimm_drvdata *ndd);
पूर्णांक nd_label_active_count(काष्ठा nvdimm_drvdata *ndd);
काष्ठा nd_namespace_label *nd_label_active(काष्ठा nvdimm_drvdata *ndd, पूर्णांक n);
u32 nd_label_alloc_slot(काष्ठा nvdimm_drvdata *ndd);
bool nd_label_मुक्त_slot(काष्ठा nvdimm_drvdata *ndd, u32 slot);
u32 nd_label_nमुक्त(काष्ठा nvdimm_drvdata *ndd);
क्रमागत nvdimm_claim_class to_nvdimm_cclass(guid_t *guid);
काष्ठा nd_region;
काष्ठा nd_namespace_pmem;
काष्ठा nd_namespace_blk;
पूर्णांक nd_pmem_namespace_label_update(काष्ठा nd_region *nd_region,
		काष्ठा nd_namespace_pmem *nspm, resource_माप_प्रकार size);
पूर्णांक nd_blk_namespace_label_update(काष्ठा nd_region *nd_region,
		काष्ठा nd_namespace_blk *nsblk, resource_माप_प्रकार size);
#पूर्ण_अगर /* __LABEL_H__ */
