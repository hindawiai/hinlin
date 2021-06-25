<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * definition क्रम store प्रणाली inक्रमmation stsi
 *
 * Copyright IBM Corp. 2001, 2008
 *
 *    Author(s): Ulrich Weigand <weigand@de.ibm.com>
 *		 Christian Borntraeger <borntraeger@de.ibm.com>
 */

#अगर_अघोषित __ASM_S390_SYSINFO_H
#घोषणा __ASM_S390_SYSINFO_H

#समावेश <यंत्र/bitsperदीर्घ.h>
#समावेश <linux/uuid.h>

काष्ठा sysinfo_1_1_1 अणु
	अचिन्हित अक्षर p:1;
	अचिन्हित अक्षर :6;
	अचिन्हित अक्षर t:1;
	अचिन्हित अक्षर :8;
	अचिन्हित अक्षर ccr;
	अचिन्हित अक्षर cai;
	अक्षर reserved_0[20];
	अचिन्हित दीर्घ lic;
	अक्षर manufacturer[16];
	अक्षर type[4];
	अक्षर reserved_1[12];
	अक्षर model_capacity[16];
	अक्षर sequence[16];
	अक्षर plant[4];
	अक्षर model[16];
	अक्षर model_perm_cap[16];
	अक्षर model_temp_cap[16];
	अचिन्हित पूर्णांक model_cap_rating;
	अचिन्हित पूर्णांक model_perm_cap_rating;
	अचिन्हित पूर्णांक model_temp_cap_rating;
	अचिन्हित अक्षर typepct[5];
	अचिन्हित अक्षर reserved_2[3];
	अचिन्हित पूर्णांक ncr;
	अचिन्हित पूर्णांक npr;
	अचिन्हित पूर्णांक ntr;
पूर्ण;

काष्ठा sysinfo_1_2_1 अणु
	अक्षर reserved_0[80];
	अक्षर sequence[16];
	अक्षर plant[4];
	अक्षर reserved_1[2];
	अचिन्हित लघु cpu_address;
पूर्ण;

काष्ठा sysinfo_1_2_2 अणु
	अक्षर क्रमmat;
	अक्षर reserved_0[1];
	अचिन्हित लघु acc_offset;
	अचिन्हित अक्षर mt_installed :1;
	अचिन्हित अक्षर :2;
	अचिन्हित अक्षर mt_stid :5;
	अचिन्हित अक्षर :3;
	अचिन्हित अक्षर mt_gtid :5;
	अक्षर reserved_1[18];
	अचिन्हित पूर्णांक nominal_cap;
	अचिन्हित पूर्णांक secondary_cap;
	अचिन्हित पूर्णांक capability;
	अचिन्हित लघु cpus_total;
	अचिन्हित लघु cpus_configured;
	अचिन्हित लघु cpus_standby;
	अचिन्हित लघु cpus_reserved;
	अचिन्हित लघु adjusपंचांगent[0];
पूर्ण;

काष्ठा sysinfo_1_2_2_extension अणु
	अचिन्हित पूर्णांक alt_capability;
	अचिन्हित लघु alt_adjusपंचांगent[0];
पूर्ण;

काष्ठा sysinfo_2_2_1 अणु
	अक्षर reserved_0[80];
	अक्षर sequence[16];
	अक्षर plant[4];
	अचिन्हित लघु cpu_id;
	अचिन्हित लघु cpu_address;
पूर्ण;

काष्ठा sysinfo_2_2_2 अणु
	अक्षर reserved_0[32];
	अचिन्हित लघु lpar_number;
	अक्षर reserved_1;
	अचिन्हित अक्षर अक्षरacteristics;
	अचिन्हित लघु cpus_total;
	अचिन्हित लघु cpus_configured;
	अचिन्हित लघु cpus_standby;
	अचिन्हित लघु cpus_reserved;
	अक्षर name[8];
	अचिन्हित पूर्णांक caf;
	अक्षर reserved_2[8];
	अचिन्हित अक्षर mt_installed :1;
	अचिन्हित अक्षर :2;
	अचिन्हित अक्षर mt_stid :5;
	अचिन्हित अक्षर :3;
	अचिन्हित अक्षर mt_gtid :5;
	अचिन्हित अक्षर :3;
	अचिन्हित अक्षर mt_psmtid :5;
	अक्षर reserved_3[5];
	अचिन्हित लघु cpus_dedicated;
	अचिन्हित लघु cpus_shared;
	अक्षर reserved_4[3];
	अचिन्हित अक्षर vsne;
	uuid_t uuid;
	अक्षर reserved_5[160];
	अक्षर ext_name[256];
पूर्ण;

#घोषणा LPAR_CHAR_DEDICATED	(1 << 7)
#घोषणा LPAR_CHAR_SHARED	(1 << 6)
#घोषणा LPAR_CHAR_LIMITED	(1 << 5)

काष्ठा sysinfo_3_2_2 अणु
	अक्षर reserved_0[31];
	अचिन्हित अक्षर :4;
	अचिन्हित अक्षर count:4;
	काष्ठा अणु
		अक्षर reserved_0[4];
		अचिन्हित लघु cpus_total;
		अचिन्हित लघु cpus_configured;
		अचिन्हित लघु cpus_standby;
		अचिन्हित लघु cpus_reserved;
		अक्षर name[8];
		अचिन्हित पूर्णांक caf;
		अक्षर cpi[16];
		अक्षर reserved_1[3];
		अचिन्हित अक्षर evmne;
		अचिन्हित पूर्णांक reserved_2;
		uuid_t uuid;
	पूर्ण vm[8];
	अक्षर reserved_3[1504];
	अक्षर ext_names[8][256];
पूर्ण;

बाह्य पूर्णांक topology_max_mnest;

/*
 * Returns the maximum nesting level supported by the cpu topology code.
 * The current maximum level is 4 which is the drawer level.
 */
अटल अंतरभूत अचिन्हित अक्षर topology_mnest_limit(व्योम)
अणु
	वापस min(topology_max_mnest, 4);
पूर्ण

#घोषणा TOPOLOGY_NR_MAG		6

काष्ठा topology_core अणु
	अचिन्हित अक्षर nl;
	अचिन्हित अक्षर reserved0[3];
	अचिन्हित अक्षर :5;
	अचिन्हित अक्षर d:1;
	अचिन्हित अक्षर pp:2;
	अचिन्हित अक्षर reserved1;
	अचिन्हित लघु origin;
	अचिन्हित दीर्घ mask;
पूर्ण;

काष्ठा topology_container अणु
	अचिन्हित अक्षर nl;
	अचिन्हित अक्षर reserved[6];
	अचिन्हित अक्षर id;
पूर्ण;

जोड़ topology_entry अणु
	अचिन्हित अक्षर nl;
	काष्ठा topology_core cpu;
	काष्ठा topology_container container;
पूर्ण;

काष्ठा sysinfo_15_1_x अणु
	अचिन्हित अक्षर reserved0[2];
	अचिन्हित लघु length;
	अचिन्हित अक्षर mag[TOPOLOGY_NR_MAG];
	अचिन्हित अक्षर reserved1;
	अचिन्हित अक्षर mnest;
	अचिन्हित अक्षर reserved2[4];
	जोड़ topology_entry tle[0];
पूर्ण;

पूर्णांक stsi(व्योम *sysinfo, पूर्णांक fc, पूर्णांक sel1, पूर्णांक sel2);

/*
 * Service level reporting पूर्णांकerface.
 */
काष्ठा service_level अणु
	काष्ठा list_head list;
	व्योम (*seq_prपूर्णांक)(काष्ठा seq_file *, काष्ठा service_level *);
पूर्ण;

पूर्णांक रेजिस्टर_service_level(काष्ठा service_level *);
पूर्णांक unरेजिस्टर_service_level(काष्ठा service_level *);

पूर्णांक sthyi_fill(व्योम *dst, u64 *rc);
#पूर्ण_अगर /* __ASM_S390_SYSINFO_H */
