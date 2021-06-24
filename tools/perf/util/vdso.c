<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <त्रुटिसं.स>
#समावेश <unistd.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <मानककोष.स>
#समावेश <linux/kernel.h>

#समावेश "vdso.h"
#समावेश "dso.h"
#समावेश <पूर्णांकernal/lib.h>
#समावेश "map.h"
#समावेश "symbol.h"
#समावेश "machine.h"
#समावेश "thread.h"
#समावेश "linux/string.h"
#समावेश <linux/zभाग.स>
#समावेश "debug.h"

/*
 * Include definition of find_map() also used in perf-पढ़ो-vdso.c क्रम
 * building perf-पढ़ो-vdso32 and perf-पढ़ो-vdsox32.
 */
#समावेश "find-map.c"

#घोषणा VDSO__TEMP_खाता_NAME "/tmp/perf-vdso.so-XXXXXX"

काष्ठा vdso_file अणु
	bool found;
	bool error;
	अक्षर temp_file_name[माप(VDSO__TEMP_खाता_NAME)];
	स्थिर अक्षर *dso_name;
	स्थिर अक्षर *पढ़ो_prog;
पूर्ण;

काष्ठा vdso_info अणु
	काष्ठा vdso_file vdso;
#अगर BITS_PER_LONG == 64
	काष्ठा vdso_file vdso32;
	काष्ठा vdso_file vdsox32;
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा vdso_info *vdso_info__new(व्योम)
अणु
	अटल स्थिर काष्ठा vdso_info vdso_info_init = अणु
		.vdso    = अणु
			.temp_file_name = VDSO__TEMP_खाता_NAME,
			.dso_name = DSO__NAME_VDSO,
		पूर्ण,
#अगर BITS_PER_LONG == 64
		.vdso32  = अणु
			.temp_file_name = VDSO__TEMP_खाता_NAME,
			.dso_name = DSO__NAME_VDSO32,
			.पढ़ो_prog = "perf-read-vdso32",
		पूर्ण,
		.vdsox32  = अणु
			.temp_file_name = VDSO__TEMP_खाता_NAME,
			.dso_name = DSO__NAME_VDSOX32,
			.पढ़ो_prog = "perf-read-vdsox32",
		पूर्ण,
#पूर्ण_अगर
	पूर्ण;

	वापस memdup(&vdso_info_init, माप(vdso_info_init));
पूर्ण

अटल अक्षर *get_file(काष्ठा vdso_file *vdso_file)
अणु
	अक्षर *vdso = शून्य;
	अक्षर *buf = शून्य;
	व्योम *start, *end;
	माप_प्रकार size;
	पूर्णांक fd;

	अगर (vdso_file->found)
		वापस vdso_file->temp_file_name;

	अगर (vdso_file->error || find_map(&start, &end, VDSO__MAP_NAME))
		वापस शून्य;

	size = end - start;

	buf = memdup(start, size);
	अगर (!buf)
		वापस शून्य;

	fd = mkstemp(vdso_file->temp_file_name);
	अगर (fd < 0)
		जाओ out;

	अगर (size == (माप_प्रकार) ग_लिखो(fd, buf, size))
		vdso = vdso_file->temp_file_name;

	बंद(fd);

 out:
	मुक्त(buf);

	vdso_file->found = (vdso != शून्य);
	vdso_file->error = !vdso_file->found;
	वापस vdso;
पूर्ण

व्योम machine__निकास_vdso(काष्ठा machine *machine)
अणु
	काष्ठा vdso_info *vdso_info = machine->vdso_info;

	अगर (!vdso_info)
		वापस;

	अगर (vdso_info->vdso.found)
		unlink(vdso_info->vdso.temp_file_name);
#अगर BITS_PER_LONG == 64
	अगर (vdso_info->vdso32.found)
		unlink(vdso_info->vdso32.temp_file_name);
	अगर (vdso_info->vdsox32.found)
		unlink(vdso_info->vdsox32.temp_file_name);
#पूर्ण_अगर

	zमुक्त(&machine->vdso_info);
पूर्ण

अटल काष्ठा dso *__machine__addnew_vdso(काष्ठा machine *machine, स्थिर अक्षर *लघु_name,
					  स्थिर अक्षर *दीर्घ_name)
अणु
	काष्ठा dso *dso;

	dso = dso__new(लघु_name);
	अगर (dso != शून्य) अणु
		__dsos__add(&machine->dsos, dso);
		dso__set_दीर्घ_name(dso, दीर्घ_name, false);
		/* Put dso here because __dsos_add alपढ़ोy got it */
		dso__put(dso);
	पूर्ण

	वापस dso;
पूर्ण

अटल क्रमागत dso_type machine__thपढ़ो_dso_type(काष्ठा machine *machine,
					      काष्ठा thपढ़ो *thपढ़ो)
अणु
	क्रमागत dso_type dso_type = DSO__TYPE_UNKNOWN;
	काष्ठा map *map;

	maps__क्रम_each_entry(thपढ़ो->maps, map) अणु
		काष्ठा dso *dso = map->dso;
		अगर (!dso || dso->दीर्घ_name[0] != '/')
			जारी;
		dso_type = dso__type(dso, machine);
		अगर (dso_type != DSO__TYPE_UNKNOWN)
			अवरोध;
	पूर्ण

	वापस dso_type;
पूर्ण

#अगर BITS_PER_LONG == 64

अटल पूर्णांक vdso__करो_copy_compat(खाता *f, पूर्णांक fd)
अणु
	अक्षर buf[4096];
	माप_प्रकार count;

	जबतक (1) अणु
		count = ख_पढ़ो(buf, 1, माप(buf), f);
		अगर (ख_त्रुटि(f))
			वापस -त्रुटि_सं;
		अगर (ख_पूर्ण(f))
			अवरोध;
		अगर (count && ग_लिखोn(fd, buf, count) != (sमाप_प्रकार)count)
			वापस -त्रुटि_सं;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vdso__copy_compat(स्थिर अक्षर *prog, पूर्णांक fd)
अणु
	खाता *f;
	पूर्णांक err;

	f = pखोलो(prog, "r");
	अगर (!f)
		वापस -त्रुटि_सं;

	err = vdso__करो_copy_compat(f, fd);

	अगर (pबंद(f) == -1)
		वापस -त्रुटि_सं;

	वापस err;
पूर्ण

अटल पूर्णांक vdso__create_compat_file(स्थिर अक्षर *prog, अक्षर *temp_name)
अणु
	पूर्णांक fd, err;

	fd = mkstemp(temp_name);
	अगर (fd < 0)
		वापस -त्रुटि_सं;

	err = vdso__copy_compat(prog, fd);

	अगर (बंद(fd) == -1)
		वापस -त्रुटि_सं;

	वापस err;
पूर्ण

अटल स्थिर अक्षर *vdso__get_compat_file(काष्ठा vdso_file *vdso_file)
अणु
	पूर्णांक err;

	अगर (vdso_file->found)
		वापस vdso_file->temp_file_name;

	अगर (vdso_file->error)
		वापस शून्य;

	err = vdso__create_compat_file(vdso_file->पढ़ो_prog,
				       vdso_file->temp_file_name);
	अगर (err) अणु
		pr_err("%s failed, error %d\n", vdso_file->पढ़ो_prog, err);
		vdso_file->error = true;
		वापस शून्य;
	पूर्ण

	vdso_file->found = true;

	वापस vdso_file->temp_file_name;
पूर्ण

अटल काष्ठा dso *__machine__findnew_compat(काष्ठा machine *machine,
					     काष्ठा vdso_file *vdso_file)
अणु
	स्थिर अक्षर *file_name;
	काष्ठा dso *dso;

	dso = __dsos__find(&machine->dsos, vdso_file->dso_name, true);
	अगर (dso)
		जाओ out;

	file_name = vdso__get_compat_file(vdso_file);
	अगर (!file_name)
		जाओ out;

	dso = __machine__addnew_vdso(machine, vdso_file->dso_name, file_name);
out:
	वापस dso;
पूर्ण

अटल पूर्णांक __machine__findnew_vdso_compat(काष्ठा machine *machine,
					  काष्ठा thपढ़ो *thपढ़ो,
					  काष्ठा vdso_info *vdso_info,
					  काष्ठा dso **dso)
अणु
	क्रमागत dso_type dso_type;

	dso_type = machine__thपढ़ो_dso_type(machine, thपढ़ो);

#अगर_अघोषित HAVE_PERF_READ_VDSO32
	अगर (dso_type == DSO__TYPE_32BIT)
		वापस 0;
#पूर्ण_अगर
#अगर_अघोषित HAVE_PERF_READ_VDSOX32
	अगर (dso_type == DSO__TYPE_X32BIT)
		वापस 0;
#पूर्ण_अगर

	चयन (dso_type) अणु
	हाल DSO__TYPE_32BIT:
		*dso = __machine__findnew_compat(machine, &vdso_info->vdso32);
		वापस 1;
	हाल DSO__TYPE_X32BIT:
		*dso = __machine__findnew_compat(machine, &vdso_info->vdsox32);
		वापस 1;
	हाल DSO__TYPE_UNKNOWN:
	हाल DSO__TYPE_64BIT:
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

#पूर्ण_अगर

अटल काष्ठा dso *machine__find_vdso(काष्ठा machine *machine,
				      काष्ठा thपढ़ो *thपढ़ो)
अणु
	काष्ठा dso *dso = शून्य;
	क्रमागत dso_type dso_type;

	dso_type = machine__thपढ़ो_dso_type(machine, thपढ़ो);
	चयन (dso_type) अणु
	हाल DSO__TYPE_32BIT:
		dso = __dsos__find(&machine->dsos, DSO__NAME_VDSO32, true);
		अगर (!dso) अणु
			dso = __dsos__find(&machine->dsos, DSO__NAME_VDSO,
					   true);
			अगर (dso && dso_type != dso__type(dso, machine))
				dso = शून्य;
		पूर्ण
		अवरोध;
	हाल DSO__TYPE_X32BIT:
		dso = __dsos__find(&machine->dsos, DSO__NAME_VDSOX32, true);
		अवरोध;
	हाल DSO__TYPE_64BIT:
	हाल DSO__TYPE_UNKNOWN:
	शेष:
		dso = __dsos__find(&machine->dsos, DSO__NAME_VDSO, true);
		अवरोध;
	पूर्ण

	वापस dso;
पूर्ण

काष्ठा dso *machine__findnew_vdso(काष्ठा machine *machine,
				  काष्ठा thपढ़ो *thपढ़ो)
अणु
	काष्ठा vdso_info *vdso_info;
	काष्ठा dso *dso = शून्य;

	करोwn_ग_लिखो(&machine->dsos.lock);
	अगर (!machine->vdso_info)
		machine->vdso_info = vdso_info__new();

	vdso_info = machine->vdso_info;
	अगर (!vdso_info)
		जाओ out_unlock;

	dso = machine__find_vdso(machine, thपढ़ो);
	अगर (dso)
		जाओ out_unlock;

#अगर BITS_PER_LONG == 64
	अगर (__machine__findnew_vdso_compat(machine, thपढ़ो, vdso_info, &dso))
		जाओ out_unlock;
#पूर्ण_अगर

	dso = __dsos__find(&machine->dsos, DSO__NAME_VDSO, true);
	अगर (!dso) अणु
		अक्षर *file;

		file = get_file(&vdso_info->vdso);
		अगर (file)
			dso = __machine__addnew_vdso(machine, DSO__NAME_VDSO, file);
	पूर्ण

out_unlock:
	dso__get(dso);
	up_ग_लिखो(&machine->dsos.lock);
	वापस dso;
पूर्ण

bool dso__is_vdso(काष्ठा dso *dso)
अणु
	वापस !म_भेद(dso->लघु_name, DSO__NAME_VDSO) ||
	       !म_भेद(dso->लघु_name, DSO__NAME_VDSO32) ||
	       !म_भेद(dso->लघु_name, DSO__NAME_VDSOX32);
पूर्ण
