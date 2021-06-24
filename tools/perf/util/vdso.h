<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_VDSO__
#घोषणा __PERF_VDSO__

#समावेश <linux/types.h>
#समावेश <माला.स>
#समावेश <stdbool.h>

#घोषणा VDSO__MAP_NAME "[vdso]"

#घोषणा DSO__NAME_VDSO    "[vdso]"
#घोषणा DSO__NAME_VDSO32  "[vdso32]"
#घोषणा DSO__NAME_VDSOX32 "[vdsox32]"

अटल अंतरभूत bool is_vdso_map(स्थिर अक्षर *filename)
अणु
	वापस !म_भेद(filename, VDSO__MAP_NAME);
पूर्ण

काष्ठा dso;

bool dso__is_vdso(काष्ठा dso *dso);

काष्ठा machine;
काष्ठा thपढ़ो;

काष्ठा dso *machine__findnew_vdso(काष्ठा machine *machine, काष्ठा thपढ़ो *thपढ़ो);
व्योम machine__निकास_vdso(काष्ठा machine *machine);

#पूर्ण_अगर /* __PERF_VDSO__ */
