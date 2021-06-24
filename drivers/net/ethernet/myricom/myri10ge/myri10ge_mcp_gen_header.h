<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __MYRI10GE_MCP_GEN_HEADER_H__
#घोषणा __MYRI10GE_MCP_GEN_HEADER_H__


#घोषणा MCP_HEADER_PTR_OFFSET  0x3c

#घोषणा MCP_TYPE_MX 0x4d582020	/* "MX  " */
#घोषणा MCP_TYPE_PCIE 0x70636965	/* "PCIE" pcie-only MCP */
#घोषणा MCP_TYPE_ETH 0x45544820	/* "ETH " */
#घोषणा MCP_TYPE_MCP0 0x4d435030	/* "MCP0" */
#घोषणा MCP_TYPE_DFLT 0x20202020	/* "    " */
#घोषणा MCP_TYPE_ETHZ 0x4554485a	/* "ETHZ" */

काष्ठा mcp_gen_header अणु
	/* the first 4 fields are filled at compile समय */
	अचिन्हित header_length;
	__be32 mcp_type;
	अक्षर version[128];
	अचिन्हित mcp_निजी;	/* poपूर्णांकer to mcp-type specअगरic काष्ठाure */

	/* filled by the MCP at run-समय */
	अचिन्हित sram_size;
	अचिन्हित string_specs;	/* either the original STRING_SPECS or a superset */
	अचिन्हित string_specs_len;

	/* Fields above this comment are guaranteed to be present.
	 *
	 * Fields below this comment are extensions added in later versions
	 * of this काष्ठा, drivers should compare the header_length against
	 * दुरत्व(field) to check whether a given MCP implements them.
	 *
	 * Never हटाओ any field.  Keep everything naturally align.
	 */

	/* Specअगरies अगर the running mcp is mcp0, 1, or 2. */
	अचिन्हित अक्षर mcp_index;
	अचिन्हित अक्षर disable_rabbit;
	अचिन्हित अक्षर unaligned_tlp;
	अचिन्हित अक्षर pcie_link_algo;
	अचिन्हित counters_addr;
	अचिन्हित copy_block_info;	/* क्रम small mcps loaded with "lload -d" */
	अचिन्हित लघु hanकरोff_id_major;	/* must be equal */
	अचिन्हित लघु hanकरोff_id_caps;	/* bitfield: new mcp must have superset */
	अचिन्हित msix_table_addr;	/* start address of msix table in firmware */
	अचिन्हित bss_addr;	/* start of bss */
	अचिन्हित features;
	अचिन्हित ee_hdr_addr;
	अचिन्हित led_pattern;
	अचिन्हित led_pattern_dflt;
	/* 8 */
पूर्ण;

काष्ठा zmcp_info अणु
	अचिन्हित info_len;
	अचिन्हित zmcp_addr;
	अचिन्हित zmcp_len;
	अचिन्हित mcp_edata;
पूर्ण;

#पूर्ण_अगर				/* __MYRI10GE_MCP_GEN_HEADER_H__ */
