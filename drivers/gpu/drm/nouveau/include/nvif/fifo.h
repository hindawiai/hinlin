<शैली गुरु>
#अगर_अघोषित __NVIF_FIFO_H__
#घोषणा __NVIF_FIFO_H__
#समावेश <nvअगर/device.h>

/* Returns mask of runlists that support a NV_DEVICE_INFO_RUNLIST_ENGINES_* type. */
u64 nvअगर_fअगरo_runlist(काष्ठा nvअगर_device *, u64 engine);

/* CE-supporting runlists (excluding GRCE, अगर others exist). */
अटल अंतरभूत u64
nvअगर_fअगरo_runlist_ce(काष्ठा nvअगर_device *device)
अणु
	u64 runmgr = nvअगर_fअगरo_runlist(device, NV_DEVICE_HOST_RUNLIST_ENGINES_GR);
	u64 runmce = nvअगर_fअगरo_runlist(device, NV_DEVICE_HOST_RUNLIST_ENGINES_CE);
	अगर (runmce && !(runmce &= ~runmgr))
		runmce = runmgr;
	वापस runmce;
पूर्ण
#पूर्ण_अगर
