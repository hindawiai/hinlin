<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __CPUPOWER_CPUPOWER_H__
#घोषणा __CPUPOWER_CPUPOWER_H__

काष्ठा cpuघातer_topology अणु
	/* Amount of CPU cores, packages and thपढ़ोs per core in the प्रणाली */
	अचिन्हित पूर्णांक cores;
	अचिन्हित पूर्णांक pkgs;
	अचिन्हित पूर्णांक thपढ़ोs; /* per core */

	/* Array माला_लो दो_स्मृतिated with cores entries, holding per core info */
	काष्ठा cpuid_core_info *core_info;
पूर्ण;

काष्ठा cpuid_core_info अणु
	पूर्णांक pkg;
	पूर्णांक core;
	पूर्णांक cpu;

	/* flags */
	अचिन्हित पूर्णांक is_online:1;
पूर्ण;

#अगर_घोषित __cplusplus
बाह्य "C" अणु
#पूर्ण_अगर

पूर्णांक get_cpu_topology(काष्ठा cpuघातer_topology *cpu_top);
व्योम cpu_topology_release(काष्ठा cpuघातer_topology cpu_top);
पूर्णांक cpuघातer_is_cpu_online(अचिन्हित पूर्णांक cpu);

#अगर_घोषित __cplusplus
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
