<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_FIRMWARE_H__
#घोषणा __NVKM_FIRMWARE_H__
#समावेश <core/option.h>
#समावेश <core/subdev.h>

पूर्णांक nvkm_firmware_get(स्थिर काष्ठा nvkm_subdev *, स्थिर अक्षर *fwname, पूर्णांक ver,
		      स्थिर काष्ठा firmware **);
व्योम nvkm_firmware_put(स्थिर काष्ठा firmware *);

पूर्णांक nvkm_firmware_load_blob(स्थिर काष्ठा nvkm_subdev *subdev, स्थिर अक्षर *path,
			    स्थिर अक्षर *name, पूर्णांक ver, काष्ठा nvkm_blob *);
पूर्णांक nvkm_firmware_load_name(स्थिर काष्ठा nvkm_subdev *subdev, स्थिर अक्षर *path,
			    स्थिर अक्षर *name, पूर्णांक ver,
			    स्थिर काष्ठा firmware **);

#घोषणा nvkm_firmware_load(s,l,o,p...) (अणु                                      \
	काष्ठा nvkm_subdev *_s = (s);                                          \
	स्थिर अक्षर *_opts = (o);                                               \
	अक्षर _option[32];                                                      \
	typeof(l[0]) *_list = (l), *_next, *_fwअगर = शून्य;                      \
	पूर्णांक _ver, _fwv, _ret = 0;                                              \
                                                                               \
	snम_लिखो(_option, माप(_option), "Nv%sFw", _opts);                   \
	_ver = nvkm_दीर्घopt(_s->device->cfgopt, _option, -2);                  \
	अगर (_ver >= -1) अणु                                                      \
		क्रम (_next = _list; !_fwअगर && _next->load; _next++) अणु          \
			अगर (_next->version == _ver)                            \
				_fwअगर = _next;                                 \
		पूर्ण                                                              \
		_ret = _fwअगर ? 0 : -EINVAL;                                    \
	पूर्ण                                                                      \
                                                                               \
	अगर (_ret == 0) अणु                                                       \
		snम_लिखो(_option, माप(_option), "Nv%sFwVer", _opts);        \
		_fwv = _fwअगर ? _fwअगर->version : -1;                            \
		_ver = nvkm_दीर्घopt(_s->device->cfgopt, _option, _fwv);        \
		क्रम (_next = _fwअगर ? _fwअगर : _list; _next->load; _next++) अणु    \
			_fwv = (_ver >= 0) ? _ver : _next->version;            \
			_ret = _next->load(p, _fwv, _next);                    \
			अगर (_ret == 0 || _ver >= 0) अणु                          \
				_fwअगर = _next;                                 \
				अवरोध;                                         \
			पूर्ण                                                      \
		पूर्ण                                                              \
	पूर्ण                                                                      \
                                                                               \
	अगर (_ret)                                                              \
		_fwअगर = ERR_PTR(_ret);                                         \
	_fwअगर;                                                                 \
पूर्ण)
#पूर्ण_अगर
