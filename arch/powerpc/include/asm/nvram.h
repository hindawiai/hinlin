<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * NVRAM definitions and access functions.
 */
#अगर_अघोषित _ASM_POWERPC_NVRAM_H
#घोषणा _ASM_POWERPC_NVRAM_H

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/list.h>
#समावेश <uapi/यंत्र/nvram.h>

/*
 * Set oops header version to distinguish between old and new क्रमmat header.
 * lnx,oops-log partition max size is 4000, header version > 4000 will
 * help in identअगरying new header.
 */
#घोषणा OOPS_HDR_VERSION 5000

काष्ठा err_log_info अणु
	__be32 error_type;
	__be32 seq_num;
पूर्ण;

काष्ठा nvram_os_partition अणु
	स्थिर अक्षर *name;
	पूर्णांक req_size;	/* desired size, in bytes */
	पूर्णांक min_size;	/* minimum acceptable size (0 means req_size) */
	दीर्घ size;	/* size of data portion (excluding err_log_info) */
	दीर्घ index;	/* offset of data portion of partition */
	bool os_partition; /* partition initialized by OS, not FW */
पूर्ण;

काष्ठा oops_log_info अणु
	__be16 version;
	__be16 report_length;
	__be64 बारtamp;
पूर्ण __attribute__((packed));

बाह्य काष्ठा nvram_os_partition oops_log_partition;

#अगर_घोषित CONFIG_PPC_PSERIES
बाह्य काष्ठा nvram_os_partition rtas_log_partition;

बाह्य पूर्णांक nvram_ग_लिखो_error_log(अक्षर * buff, पूर्णांक length,
					 अचिन्हित पूर्णांक err_type, अचिन्हित पूर्णांक err_seq);
बाह्य पूर्णांक nvram_पढ़ो_error_log(अक्षर * buff, पूर्णांक length,
					 अचिन्हित पूर्णांक * err_type, अचिन्हित पूर्णांक *err_seq);
बाह्य पूर्णांक nvram_clear_error_log(व्योम);
बाह्य पूर्णांक pSeries_nvram_init(व्योम);
#पूर्ण_अगर /* CONFIG_PPC_PSERIES */

#अगर_घोषित CONFIG_MMIO_NVRAM
बाह्य पूर्णांक mmio_nvram_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक mmio_nvram_init(व्योम)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

बाह्य पूर्णांक __init nvram_scan_partitions(व्योम);
बाह्य loff_t nvram_create_partition(स्थिर अक्षर *name, पूर्णांक sig,
				     पूर्णांक req_size, पूर्णांक min_size);
बाह्य पूर्णांक nvram_हटाओ_partition(स्थिर अक्षर *name, पूर्णांक sig,
					स्थिर अक्षर *exceptions[]);
बाह्य पूर्णांक nvram_get_partition_size(loff_t data_index);
बाह्य loff_t nvram_find_partition(स्थिर अक्षर *name, पूर्णांक sig, पूर्णांक *out_size);

/* Return partition offset in nvram */
बाह्य पूर्णांक	pmac_get_partition(पूर्णांक partition);

/* Direct access to XPRAM on PowerMacs */
बाह्य u8	pmac_xpram_पढ़ो(पूर्णांक xpaddr);
बाह्य व्योम	pmac_xpram_ग_लिखो(पूर्णांक xpaddr, u8 data);

/* Initialize NVRAM OS partition */
बाह्य पूर्णांक __init nvram_init_os_partition(काष्ठा nvram_os_partition *part);

/* Initialize NVRAM oops partition */
बाह्य व्योम __init nvram_init_oops_partition(पूर्णांक rtas_partition_exists);

/* Read a NVRAM partition */
बाह्य पूर्णांक nvram_पढ़ो_partition(काष्ठा nvram_os_partition *part, अक्षर *buff,
				पूर्णांक length, अचिन्हित पूर्णांक *err_type,
				अचिन्हित पूर्णांक *error_log_cnt);

/* Write to NVRAM OS partition */
बाह्य पूर्णांक nvram_ग_लिखो_os_partition(काष्ठा nvram_os_partition *part,
				    अक्षर *buff, पूर्णांक length,
				    अचिन्हित पूर्णांक err_type,
				    अचिन्हित पूर्णांक error_log_cnt);

#पूर्ण_अगर /* _ASM_POWERPC_NVRAM_H */
