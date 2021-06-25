<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#अगर_अघोषित _DISCOVERY_H_
#घोषणा _DISCOVERY_H_

#घोषणा PSP_HEADER_SIZE                 256
#घोषणा BINARY_SIGNATURE                0x28211407
#घोषणा DISCOVERY_TABLE_SIGNATURE       0x53445049

प्रकार क्रमागत
अणु
	IP_DISCOVERY = 0,
	GC,
	HARVEST_INFO,
	TABLE_4,
	RESERVED_1,
	RESERVED_2,
	TOTAL_TABLES = 6
पूर्ण table;

#आशय pack(1)

प्रकार काष्ठा table_info
अणु
	uपूर्णांक16_t offset;   /* Byte offset */
	uपूर्णांक16_t checksum; /* Byte sum of the table */
	uपूर्णांक16_t size;     /* Table size */
	uपूर्णांक16_t padding;
पूर्ण table_info;

प्रकार काष्ठा binary_header
अणु
	/* psp काष्ठाure should go at the top of this काष्ठाure */
	uपूर्णांक32_t binary_signature; /* 0x7, 0x14, 0x21, 0x28 */
	uपूर्णांक16_t version_major;
	uपूर्णांक16_t version_minor;
	uपूर्णांक16_t binary_checksum;  /* Byte sum of the binary after this field */
	uपूर्णांक16_t binary_size;      /* Binary Size*/
	table_info table_list[TOTAL_TABLES];
पूर्ण binary_header;

प्रकार काष्ठा die_info
अणु
	uपूर्णांक16_t die_id;
	uपूर्णांक16_t die_offset; /* Poपूर्णांकs to the corresponding die_header काष्ठाure */
पूर्ण die_info;


प्रकार काष्ठा ip_discovery_header
अणु
	uपूर्णांक32_t signature;    /* Table Signature */
	uपूर्णांक16_t version;      /* Table Version */
	uपूर्णांक16_t size;         /* Table Size */
	uपूर्णांक32_t id;           /* Table ID */
	uपूर्णांक16_t num_dies;     /* Number of Dies */
	die_info die_info[16]; /* list die inक्रमmation क्रम up to 16 dies */
	uपूर्णांक16_t padding[1];   /* padding */
पूर्ण ip_discovery_header;

प्रकार काष्ठा ip
अणु
	uपूर्णांक16_t hw_id;           /* Hardware ID */
	uपूर्णांक8_t number_instance;  /* instance of the IP */
	uपूर्णांक8_t num_base_address; /* Number of Base Addresses */
	uपूर्णांक8_t major;            /* HCID Major */
	uपूर्णांक8_t minor;            /* HCID Minor */
	uपूर्णांक8_t revision;         /* HCID Revision */
#अगर defined(__BIG_ENDIAN)
	uपूर्णांक8_t reserved : 4;     /* Placeholder field */
	uपूर्णांक8_t harvest : 4;      /* Harvest */
#अन्यथा
	uपूर्णांक8_t harvest : 4;      /* Harvest */
	uपूर्णांक8_t reserved : 4;     /* Placeholder field */
#पूर्ण_अगर
	uपूर्णांक32_t base_address[1]; /* variable number of Addresses */
पूर्ण ip;

प्रकार काष्ठा die_header
अणु
	uपूर्णांक16_t die_id;
	uपूर्णांक16_t num_ips;
पूर्ण die_header;

प्रकार काष्ठा ip_काष्ठाure
अणु
	ip_discovery_header* header;
	काष्ठा die
	अणु
		die_header *die_header;
		ip *ip_list;
	पूर्ण die;
पूर्ण ip_काष्ठाure;

काष्ठा gpu_info_header अणु
	uपूर्णांक32_t table_id;      /* table ID */
	uपूर्णांक16_t version_major; /* table version */
	uपूर्णांक16_t version_minor; /* table version */
	uपूर्णांक32_t size;          /* size of the entire header+data in bytes */
पूर्ण;

काष्ठा gc_info_v1_0 अणु
	काष्ठा gpu_info_header header;

	uपूर्णांक32_t gc_num_se;
	uपूर्णांक32_t gc_num_wgp0_per_sa;
	uपूर्णांक32_t gc_num_wgp1_per_sa;
	uपूर्णांक32_t gc_num_rb_per_se;
	uपूर्णांक32_t gc_num_gl2c;
	uपूर्णांक32_t gc_num_gprs;
	uपूर्णांक32_t gc_num_max_gs_thds;
	uपूर्णांक32_t gc_gs_table_depth;
	uपूर्णांक32_t gc_gsprim_buff_depth;
	uपूर्णांक32_t gc_parameter_cache_depth;
	uपूर्णांक32_t gc_द्विगुन_offchip_lds_buffer;
	uपूर्णांक32_t gc_wave_size;
	uपूर्णांक32_t gc_max_waves_per_simd;
	uपूर्णांक32_t gc_max_scratch_slots_per_cu;
	uपूर्णांक32_t gc_lds_size;
	uपूर्णांक32_t gc_num_sc_per_se;
	uपूर्णांक32_t gc_num_sa_per_se;
	uपूर्णांक32_t gc_num_packer_per_sc;
	uपूर्णांक32_t gc_num_gl2a;
पूर्ण;

प्रकार काष्ठा harvest_info_header अणु
	uपूर्णांक32_t signature; /* Table Signature */
	uपूर्णांक32_t version;   /* Table Version */
पूर्ण harvest_info_header;

प्रकार काष्ठा harvest_info अणु
	uपूर्णांक16_t hw_id;          /* Hardware ID */
	uपूर्णांक8_t number_instance; /* Instance of the IP */
	uपूर्णांक8_t reserved;        /* Reserved क्रम alignment */
पूर्ण harvest_info;

प्रकार काष्ठा harvest_table अणु
	harvest_info_header header;
	harvest_info list[32];
पूर्ण harvest_table;

#आशय pack()

#पूर्ण_अगर
