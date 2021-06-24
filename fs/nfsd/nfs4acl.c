<शैली गुरु>
/*
 *  Common NFSv4 ACL handling code.
 *
 *  Copyright (c) 2002, 2003 The Regents of the University of Michigan.
 *  All rights reserved.
 *
 *  Marius Aamodt Eriksen <marius@umich.edu>
 *  Jeff Sedlak <jsedlak@umich.edu>
 *  J. Bruce Fields <bfields@umich.edu>
 *
 *  Redistribution and use in source and binary क्रमms, with or without
 *  modअगरication, are permitted provided that the following conditions
 *  are met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary क्रमm must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     करोcumentation and/or other materials provided with the distribution.
 *  3. Neither the name of the University nor the names of its
 *     contributors may be used to enकरोrse or promote products derived
 *     from this software without specअगरic prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 *  FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 *  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/posix_acl.h>

#समावेश "nfsfh.h"
#समावेश "nfsd.h"
#समावेश "acl.h"
#समावेश "vfs.h"

#घोषणा NFS4_ACL_TYPE_DEFAULT	0x01
#घोषणा NFS4_ACL_सूची		0x02
#घोषणा NFS4_ACL_OWNER		0x04

/* mode bit translations: */
#घोषणा NFS4_READ_MODE (NFS4_ACE_READ_DATA)
#घोषणा NFS4_WRITE_MODE (NFS4_ACE_WRITE_DATA | NFS4_ACE_APPEND_DATA)
#घोषणा NFS4_EXECUTE_MODE NFS4_ACE_EXECUTE
#घोषणा NFS4_ANYONE_MODE (NFS4_ACE_READ_ATTRIBUTES | NFS4_ACE_READ_ACL | NFS4_ACE_SYNCHRONIZE)
#घोषणा NFS4_OWNER_MODE (NFS4_ACE_WRITE_ATTRIBUTES | NFS4_ACE_WRITE_ACL)

/* flags used to simulate posix शेष ACLs */
#घोषणा NFS4_INHERITANCE_FLAGS (NFS4_ACE_खाता_INHERIT_ACE \
		| NFS4_ACE_सूचीECTORY_INHERIT_ACE)

#घोषणा NFS4_SUPPORTED_FLAGS (NFS4_INHERITANCE_FLAGS \
		| NFS4_ACE_INHERIT_ONLY_ACE \
		| NFS4_ACE_IDENTIFIER_GROUP)

अटल u32
mask_from_posix(अचिन्हित लघु perm, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक mask = NFS4_ANYONE_MODE;

	अगर (flags & NFS4_ACL_OWNER)
		mask |= NFS4_OWNER_MODE;
	अगर (perm & ACL_READ)
		mask |= NFS4_READ_MODE;
	अगर (perm & ACL_WRITE)
		mask |= NFS4_WRITE_MODE;
	अगर ((perm & ACL_WRITE) && (flags & NFS4_ACL_सूची))
		mask |= NFS4_ACE_DELETE_CHILD;
	अगर (perm & ACL_EXECUTE)
		mask |= NFS4_EXECUTE_MODE;
	वापस mask;
पूर्ण

अटल u32
deny_mask_from_posix(अचिन्हित लघु perm, u32 flags)
अणु
	u32 mask = 0;

	अगर (perm & ACL_READ)
		mask |= NFS4_READ_MODE;
	अगर (perm & ACL_WRITE)
		mask |= NFS4_WRITE_MODE;
	अगर ((perm & ACL_WRITE) && (flags & NFS4_ACL_सूची))
		mask |= NFS4_ACE_DELETE_CHILD;
	अगर (perm & ACL_EXECUTE)
		mask |= NFS4_EXECUTE_MODE;
	वापस mask;
पूर्ण

/* XXX: modअगरy functions to वापस NFS errors; they're only ever
 * used by nfs code, after all.... */

/* We only map from NFSv4 to POSIX ACLs when setting ACLs, when we err on the
 * side of being more restrictive, so the mode bit mapping below is
 * pessimistic.  An optimistic version would be needed to handle DENY's,
 * but we expect to coalesce all ALLOWs and DENYs beक्रमe mapping to mode
 * bits. */

अटल व्योम
low_mode_from_nfs4(u32 perm, अचिन्हित लघु *mode, अचिन्हित पूर्णांक flags)
अणु
	u32 ग_लिखो_mode = NFS4_WRITE_MODE;

	अगर (flags & NFS4_ACL_सूची)
		ग_लिखो_mode |= NFS4_ACE_DELETE_CHILD;
	*mode = 0;
	अगर ((perm & NFS4_READ_MODE) == NFS4_READ_MODE)
		*mode |= ACL_READ;
	अगर ((perm & ग_लिखो_mode) == ग_लिखो_mode)
		*mode |= ACL_WRITE;
	अगर ((perm & NFS4_EXECUTE_MODE) == NFS4_EXECUTE_MODE)
		*mode |= ACL_EXECUTE;
पूर्ण

अटल लघु ace2type(काष्ठा nfs4_ace *);
अटल व्योम _posix_to_nfsv4_one(काष्ठा posix_acl *, काष्ठा nfs4_acl *,
				अचिन्हित पूर्णांक);

पूर्णांक
nfsd4_get_nfs4_acl(काष्ठा svc_rqst *rqstp, काष्ठा dentry *dentry,
		काष्ठा nfs4_acl **acl)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	पूर्णांक error = 0;
	काष्ठा posix_acl *pacl = शून्य, *dpacl = शून्य;
	अचिन्हित पूर्णांक flags = 0;
	पूर्णांक size = 0;

	pacl = get_acl(inode, ACL_TYPE_ACCESS);
	अगर (!pacl)
		pacl = posix_acl_from_mode(inode->i_mode, GFP_KERNEL);

	अगर (IS_ERR(pacl))
		वापस PTR_ERR(pacl);

	/* allocate क्रम worst हाल: one (deny, allow) pair each: */
	size += 2 * pacl->a_count;

	अगर (S_ISसूची(inode->i_mode)) अणु
		flags = NFS4_ACL_सूची;
		dpacl = get_acl(inode, ACL_TYPE_DEFAULT);
		अगर (IS_ERR(dpacl)) अणु
			error = PTR_ERR(dpacl);
			जाओ rel_pacl;
		पूर्ण

		अगर (dpacl)
			size += 2 * dpacl->a_count;
	पूर्ण

	*acl = kदो_स्मृति(nfs4_acl_bytes(size), GFP_KERNEL);
	अगर (*acl == शून्य) अणु
		error = -ENOMEM;
		जाओ out;
	पूर्ण
	(*acl)->naces = 0;

	_posix_to_nfsv4_one(pacl, *acl, flags & ~NFS4_ACL_TYPE_DEFAULT);

	अगर (dpacl)
		_posix_to_nfsv4_one(dpacl, *acl, flags | NFS4_ACL_TYPE_DEFAULT);

out:
	posix_acl_release(dpacl);
rel_pacl:
	posix_acl_release(pacl);
	वापस error;
पूर्ण

काष्ठा posix_acl_summary अणु
	अचिन्हित लघु owner;
	अचिन्हित लघु users;
	अचिन्हित लघु group;
	अचिन्हित लघु groups;
	अचिन्हित लघु other;
	अचिन्हित लघु mask;
पूर्ण;

अटल व्योम
summarize_posix_acl(काष्ठा posix_acl *acl, काष्ठा posix_acl_summary *pas)
अणु
	काष्ठा posix_acl_entry *pa, *pe;

	/*
	 * Only pas.users and pas.groups need initialization; previous
	 * posix_acl_valid() calls ensure that the other fields will be
	 * initialized in the following loop.  But, just to placate gcc:
	 */
	स_रखो(pas, 0, माप(*pas));
	pas->mask = 07;

	pe = acl->a_entries + acl->a_count;

	FOREACH_ACL_ENTRY(pa, acl, pe) अणु
		चयन (pa->e_tag) अणु
			हाल ACL_USER_OBJ:
				pas->owner = pa->e_perm;
				अवरोध;
			हाल ACL_GROUP_OBJ:
				pas->group = pa->e_perm;
				अवरोध;
			हाल ACL_USER:
				pas->users |= pa->e_perm;
				अवरोध;
			हाल ACL_GROUP:
				pas->groups |= pa->e_perm;
				अवरोध;
			हाल ACL_OTHER:
				pas->other = pa->e_perm;
				अवरोध;
			हाल ACL_MASK:
				pas->mask = pa->e_perm;
				अवरोध;
		पूर्ण
	पूर्ण
	/* We'll only care about effective permissions: */
	pas->users &= pas->mask;
	pas->group &= pas->mask;
	pas->groups &= pas->mask;
पूर्ण

/* We assume the acl has been verअगरied with posix_acl_valid. */
अटल व्योम
_posix_to_nfsv4_one(काष्ठा posix_acl *pacl, काष्ठा nfs4_acl *acl,
						अचिन्हित पूर्णांक flags)
अणु
	काष्ठा posix_acl_entry *pa, *group_owner_entry;
	काष्ठा nfs4_ace *ace;
	काष्ठा posix_acl_summary pas;
	अचिन्हित लघु deny;
	पूर्णांक eflag = ((flags & NFS4_ACL_TYPE_DEFAULT) ?
		NFS4_INHERITANCE_FLAGS | NFS4_ACE_INHERIT_ONLY_ACE : 0);

	BUG_ON(pacl->a_count < 3);
	summarize_posix_acl(pacl, &pas);

	pa = pacl->a_entries;
	ace = acl->aces + acl->naces;

	/* We could deny everything not granted by the owner: */
	deny = ~pas.owner;
	/*
	 * but it is equivalent (and simpler) to deny only what is not
	 * granted by later entries:
	 */
	deny &= pas.users | pas.group | pas.groups | pas.other;
	अगर (deny) अणु
		ace->type = NFS4_ACE_ACCESS_DENIED_ACE_TYPE;
		ace->flag = eflag;
		ace->access_mask = deny_mask_from_posix(deny, flags);
		ace->whotype = NFS4_ACL_WHO_OWNER;
		ace++;
		acl->naces++;
	पूर्ण

	ace->type = NFS4_ACE_ACCESS_ALLOWED_ACE_TYPE;
	ace->flag = eflag;
	ace->access_mask = mask_from_posix(pa->e_perm, flags | NFS4_ACL_OWNER);
	ace->whotype = NFS4_ACL_WHO_OWNER;
	ace++;
	acl->naces++;
	pa++;

	जबतक (pa->e_tag == ACL_USER) अणु
		deny = ~(pa->e_perm & pas.mask);
		deny &= pas.groups | pas.group | pas.other;
		अगर (deny) अणु
			ace->type = NFS4_ACE_ACCESS_DENIED_ACE_TYPE;
			ace->flag = eflag;
			ace->access_mask = deny_mask_from_posix(deny, flags);
			ace->whotype = NFS4_ACL_WHO_NAMED;
			ace->who_uid = pa->e_uid;
			ace++;
			acl->naces++;
		पूर्ण
		ace->type = NFS4_ACE_ACCESS_ALLOWED_ACE_TYPE;
		ace->flag = eflag;
		ace->access_mask = mask_from_posix(pa->e_perm & pas.mask,
						   flags);
		ace->whotype = NFS4_ACL_WHO_NAMED;
		ace->who_uid = pa->e_uid;
		ace++;
		acl->naces++;
		pa++;
	पूर्ण

	/* In the हाल of groups, we apply allow ACEs first, then deny ACEs,
	 * since a user can be in more than one group.  */

	/* allow ACEs */

	group_owner_entry = pa;

	ace->type = NFS4_ACE_ACCESS_ALLOWED_ACE_TYPE;
	ace->flag = eflag;
	ace->access_mask = mask_from_posix(pas.group, flags);
	ace->whotype = NFS4_ACL_WHO_GROUP;
	ace++;
	acl->naces++;
	pa++;

	जबतक (pa->e_tag == ACL_GROUP) अणु
		ace->type = NFS4_ACE_ACCESS_ALLOWED_ACE_TYPE;
		ace->flag = eflag | NFS4_ACE_IDENTIFIER_GROUP;
		ace->access_mask = mask_from_posix(pa->e_perm & pas.mask,
						   flags);
		ace->whotype = NFS4_ACL_WHO_NAMED;
		ace->who_gid = pa->e_gid;
		ace++;
		acl->naces++;
		pa++;
	पूर्ण

	/* deny ACEs */

	pa = group_owner_entry;

	deny = ~pas.group & pas.other;
	अगर (deny) अणु
		ace->type = NFS4_ACE_ACCESS_DENIED_ACE_TYPE;
		ace->flag = eflag;
		ace->access_mask = deny_mask_from_posix(deny, flags);
		ace->whotype = NFS4_ACL_WHO_GROUP;
		ace++;
		acl->naces++;
	पूर्ण
	pa++;

	जबतक (pa->e_tag == ACL_GROUP) अणु
		deny = ~(pa->e_perm & pas.mask);
		deny &= pas.other;
		अगर (deny) अणु
			ace->type = NFS4_ACE_ACCESS_DENIED_ACE_TYPE;
			ace->flag = eflag | NFS4_ACE_IDENTIFIER_GROUP;
			ace->access_mask = deny_mask_from_posix(deny, flags);
			ace->whotype = NFS4_ACL_WHO_NAMED;
			ace->who_gid = pa->e_gid;
			ace++;
			acl->naces++;
		पूर्ण
		pa++;
	पूर्ण

	अगर (pa->e_tag == ACL_MASK)
		pa++;
	ace->type = NFS4_ACE_ACCESS_ALLOWED_ACE_TYPE;
	ace->flag = eflag;
	ace->access_mask = mask_from_posix(pa->e_perm, flags);
	ace->whotype = NFS4_ACL_WHO_EVERYONE;
	acl->naces++;
पूर्ण

अटल bool
pace_gt(काष्ठा posix_acl_entry *pace1, काष्ठा posix_acl_entry *pace2)
अणु
	अगर (pace1->e_tag != pace2->e_tag)
		वापस pace1->e_tag > pace2->e_tag;
	अगर (pace1->e_tag == ACL_USER)
		वापस uid_gt(pace1->e_uid, pace2->e_uid);
	अगर (pace1->e_tag == ACL_GROUP)
		वापस gid_gt(pace1->e_gid, pace2->e_gid);
	वापस false;
पूर्ण

अटल व्योम
sort_pacl_range(काष्ठा posix_acl *pacl, पूर्णांक start, पूर्णांक end) अणु
	पूर्णांक sorted = 0, i;

	/* We just करो a bubble sort; easy to करो in place, and we're not
	 * expecting acl's to be दीर्घ enough to justअगरy anything more. */
	जबतक (!sorted) अणु
		sorted = 1;
		क्रम (i = start; i < end; i++) अणु
			अगर (pace_gt(&pacl->a_entries[i],
				    &pacl->a_entries[i+1])) अणु
				sorted = 0;
				swap(pacl->a_entries[i],
				     pacl->a_entries[i + 1]);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
sort_pacl(काष्ठा posix_acl *pacl)
अणु
	/* posix_acl_valid requires that users and groups be in order
	 * by uid/gid. */
	पूर्णांक i, j;

	/* no users or groups */
	अगर (!pacl || pacl->a_count <= 4)
		वापस;

	i = 1;
	जबतक (pacl->a_entries[i].e_tag == ACL_USER)
		i++;
	sort_pacl_range(pacl, 1, i-1);

	BUG_ON(pacl->a_entries[i].e_tag != ACL_GROUP_OBJ);
	j = ++i;
	जबतक (pacl->a_entries[j].e_tag == ACL_GROUP)
		j++;
	sort_pacl_range(pacl, i, j-1);
	वापस;
पूर्ण

/*
 * While processing the NFSv4 ACE, this मुख्यtains biपंचांगasks representing
 * which permission bits have been allowed and which denied to a given
 * entity: */
काष्ठा posix_ace_state अणु
	u32 allow;
	u32 deny;
पूर्ण;

काष्ठा posix_user_ace_state अणु
	जोड़ अणु
		kuid_t uid;
		kgid_t gid;
	पूर्ण;
	काष्ठा posix_ace_state perms;
पूर्ण;

काष्ठा posix_ace_state_array अणु
	पूर्णांक n;
	काष्ठा posix_user_ace_state aces[];
पूर्ण;

/*
 * While processing the NFSv4 ACE, this मुख्यtains the partial permissions
 * calculated so far: */

काष्ठा posix_acl_state अणु
	पूर्णांक empty;
	काष्ठा posix_ace_state owner;
	काष्ठा posix_ace_state group;
	काष्ठा posix_ace_state other;
	काष्ठा posix_ace_state everyone;
	काष्ठा posix_ace_state mask; /* Deny unused in this हाल */
	काष्ठा posix_ace_state_array *users;
	काष्ठा posix_ace_state_array *groups;
पूर्ण;

अटल पूर्णांक
init_state(काष्ठा posix_acl_state *state, पूर्णांक cnt)
अणु
	पूर्णांक alloc;

	स_रखो(state, 0, माप(काष्ठा posix_acl_state));
	state->empty = 1;
	/*
	 * In the worst हाल, each inभागidual acl could be क्रम a distinct
	 * named user or group, but we करोn't know which, so we allocate
	 * enough space क्रम either:
	 */
	alloc = माप(काष्ठा posix_ace_state_array)
		+ cnt*माप(काष्ठा posix_user_ace_state);
	state->users = kzalloc(alloc, GFP_KERNEL);
	अगर (!state->users)
		वापस -ENOMEM;
	state->groups = kzalloc(alloc, GFP_KERNEL);
	अगर (!state->groups) अणु
		kमुक्त(state->users);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
मुक्त_state(काष्ठा posix_acl_state *state) अणु
	kमुक्त(state->users);
	kमुक्त(state->groups);
पूर्ण

अटल अंतरभूत व्योम add_to_mask(काष्ठा posix_acl_state *state, काष्ठा posix_ace_state *astate)
अणु
	state->mask.allow |= astate->allow;
पूर्ण

अटल काष्ठा posix_acl *
posix_state_to_acl(काष्ठा posix_acl_state *state, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा posix_acl_entry *pace;
	काष्ठा posix_acl *pacl;
	पूर्णांक nace;
	पूर्णांक i;

	/*
	 * ACLs with no ACEs are treated dअगरferently in the inheritable
	 * and effective हालs: when there are no inheritable ACEs,
	 * calls ->set_acl with a शून्य ACL काष्ठाure.
	 */
	अगर (state->empty && (flags & NFS4_ACL_TYPE_DEFAULT))
		वापस शून्य;

	/*
	 * When there are no effective ACEs, the following will end
	 * up setting a 3-element effective posix ACL with all
	 * permissions zero.
	 */
	अगर (!state->users->n && !state->groups->n)
		nace = 3;
	अन्यथा /* Note we also include a MASK ACE in this हाल: */
		nace = 4 + state->users->n + state->groups->n;
	pacl = posix_acl_alloc(nace, GFP_KERNEL);
	अगर (!pacl)
		वापस ERR_PTR(-ENOMEM);

	pace = pacl->a_entries;
	pace->e_tag = ACL_USER_OBJ;
	low_mode_from_nfs4(state->owner.allow, &pace->e_perm, flags);

	क्रम (i=0; i < state->users->n; i++) अणु
		pace++;
		pace->e_tag = ACL_USER;
		low_mode_from_nfs4(state->users->aces[i].perms.allow,
					&pace->e_perm, flags);
		pace->e_uid = state->users->aces[i].uid;
		add_to_mask(state, &state->users->aces[i].perms);
	पूर्ण

	pace++;
	pace->e_tag = ACL_GROUP_OBJ;
	low_mode_from_nfs4(state->group.allow, &pace->e_perm, flags);
	add_to_mask(state, &state->group);

	क्रम (i=0; i < state->groups->n; i++) अणु
		pace++;
		pace->e_tag = ACL_GROUP;
		low_mode_from_nfs4(state->groups->aces[i].perms.allow,
					&pace->e_perm, flags);
		pace->e_gid = state->groups->aces[i].gid;
		add_to_mask(state, &state->groups->aces[i].perms);
	पूर्ण

	अगर (state->users->n || state->groups->n) अणु
		pace++;
		pace->e_tag = ACL_MASK;
		low_mode_from_nfs4(state->mask.allow, &pace->e_perm, flags);
	पूर्ण

	pace++;
	pace->e_tag = ACL_OTHER;
	low_mode_from_nfs4(state->other.allow, &pace->e_perm, flags);

	वापस pacl;
पूर्ण

अटल अंतरभूत व्योम allow_bits(काष्ठा posix_ace_state *astate, u32 mask)
अणु
	/* Allow all bits in the mask not alपढ़ोy denied: */
	astate->allow |= mask & ~astate->deny;
पूर्ण

अटल अंतरभूत व्योम deny_bits(काष्ठा posix_ace_state *astate, u32 mask)
अणु
	/* Deny all bits in the mask not alपढ़ोy allowed: */
	astate->deny |= mask & ~astate->allow;
पूर्ण

अटल पूर्णांक find_uid(काष्ठा posix_acl_state *state, kuid_t uid)
अणु
	काष्ठा posix_ace_state_array *a = state->users;
	पूर्णांक i;

	क्रम (i = 0; i < a->n; i++)
		अगर (uid_eq(a->aces[i].uid, uid))
			वापस i;
	/* Not found: */
	a->n++;
	a->aces[i].uid = uid;
	a->aces[i].perms.allow = state->everyone.allow;
	a->aces[i].perms.deny  = state->everyone.deny;

	वापस i;
पूर्ण

अटल पूर्णांक find_gid(काष्ठा posix_acl_state *state, kgid_t gid)
अणु
	काष्ठा posix_ace_state_array *a = state->groups;
	पूर्णांक i;

	क्रम (i = 0; i < a->n; i++)
		अगर (gid_eq(a->aces[i].gid, gid))
			वापस i;
	/* Not found: */
	a->n++;
	a->aces[i].gid = gid;
	a->aces[i].perms.allow = state->everyone.allow;
	a->aces[i].perms.deny  = state->everyone.deny;

	वापस i;
पूर्ण

अटल व्योम deny_bits_array(काष्ठा posix_ace_state_array *a, u32 mask)
अणु
	पूर्णांक i;

	क्रम (i=0; i < a->n; i++)
		deny_bits(&a->aces[i].perms, mask);
पूर्ण

अटल व्योम allow_bits_array(काष्ठा posix_ace_state_array *a, u32 mask)
अणु
	पूर्णांक i;

	क्रम (i=0; i < a->n; i++)
		allow_bits(&a->aces[i].perms, mask);
पूर्ण

अटल व्योम process_one_v4_ace(काष्ठा posix_acl_state *state,
				काष्ठा nfs4_ace *ace)
अणु
	u32 mask = ace->access_mask;
	पूर्णांक i;

	state->empty = 0;

	चयन (ace2type(ace)) अणु
	हाल ACL_USER_OBJ:
		अगर (ace->type == NFS4_ACE_ACCESS_ALLOWED_ACE_TYPE) अणु
			allow_bits(&state->owner, mask);
		पूर्ण अन्यथा अणु
			deny_bits(&state->owner, mask);
		पूर्ण
		अवरोध;
	हाल ACL_USER:
		i = find_uid(state, ace->who_uid);
		अगर (ace->type == NFS4_ACE_ACCESS_ALLOWED_ACE_TYPE) अणु
			allow_bits(&state->users->aces[i].perms, mask);
		पूर्ण अन्यथा अणु
			deny_bits(&state->users->aces[i].perms, mask);
			mask = state->users->aces[i].perms.deny;
			deny_bits(&state->owner, mask);
		पूर्ण
		अवरोध;
	हाल ACL_GROUP_OBJ:
		अगर (ace->type == NFS4_ACE_ACCESS_ALLOWED_ACE_TYPE) अणु
			allow_bits(&state->group, mask);
		पूर्ण अन्यथा अणु
			deny_bits(&state->group, mask);
			mask = state->group.deny;
			deny_bits(&state->owner, mask);
			deny_bits(&state->everyone, mask);
			deny_bits_array(state->users, mask);
			deny_bits_array(state->groups, mask);
		पूर्ण
		अवरोध;
	हाल ACL_GROUP:
		i = find_gid(state, ace->who_gid);
		अगर (ace->type == NFS4_ACE_ACCESS_ALLOWED_ACE_TYPE) अणु
			allow_bits(&state->groups->aces[i].perms, mask);
		पूर्ण अन्यथा अणु
			deny_bits(&state->groups->aces[i].perms, mask);
			mask = state->groups->aces[i].perms.deny;
			deny_bits(&state->owner, mask);
			deny_bits(&state->group, mask);
			deny_bits(&state->everyone, mask);
			deny_bits_array(state->users, mask);
			deny_bits_array(state->groups, mask);
		पूर्ण
		अवरोध;
	हाल ACL_OTHER:
		अगर (ace->type == NFS4_ACE_ACCESS_ALLOWED_ACE_TYPE) अणु
			allow_bits(&state->owner, mask);
			allow_bits(&state->group, mask);
			allow_bits(&state->other, mask);
			allow_bits(&state->everyone, mask);
			allow_bits_array(state->users, mask);
			allow_bits_array(state->groups, mask);
		पूर्ण अन्यथा अणु
			deny_bits(&state->owner, mask);
			deny_bits(&state->group, mask);
			deny_bits(&state->other, mask);
			deny_bits(&state->everyone, mask);
			deny_bits_array(state->users, mask);
			deny_bits_array(state->groups, mask);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक nfs4_acl_nfsv4_to_posix(काष्ठा nfs4_acl *acl,
		काष्ठा posix_acl **pacl, काष्ठा posix_acl **dpacl,
		अचिन्हित पूर्णांक flags)
अणु
	काष्ठा posix_acl_state effective_acl_state, शेष_acl_state;
	काष्ठा nfs4_ace *ace;
	पूर्णांक ret;

	ret = init_state(&effective_acl_state, acl->naces);
	अगर (ret)
		वापस ret;
	ret = init_state(&शेष_acl_state, acl->naces);
	अगर (ret)
		जाओ out_estate;
	ret = -EINVAL;
	क्रम (ace = acl->aces; ace < acl->aces + acl->naces; ace++) अणु
		अगर (ace->type != NFS4_ACE_ACCESS_ALLOWED_ACE_TYPE &&
		    ace->type != NFS4_ACE_ACCESS_DENIED_ACE_TYPE)
			जाओ out_dstate;
		अगर (ace->flag & ~NFS4_SUPPORTED_FLAGS)
			जाओ out_dstate;
		अगर ((ace->flag & NFS4_INHERITANCE_FLAGS) == 0) अणु
			process_one_v4_ace(&effective_acl_state, ace);
			जारी;
		पूर्ण
		अगर (!(flags & NFS4_ACL_सूची))
			जाओ out_dstate;
		/*
		 * Note that when only one of खाता_INHERIT or सूचीECTORY_INHERIT
		 * is set, we're effectively turning on the other.  That's OK,
		 * according to rfc 3530.
		 */
		process_one_v4_ace(&शेष_acl_state, ace);

		अगर (!(ace->flag & NFS4_ACE_INHERIT_ONLY_ACE))
			process_one_v4_ace(&effective_acl_state, ace);
	पूर्ण
	*pacl = posix_state_to_acl(&effective_acl_state, flags);
	अगर (IS_ERR(*pacl)) अणु
		ret = PTR_ERR(*pacl);
		*pacl = शून्य;
		जाओ out_dstate;
	पूर्ण
	*dpacl = posix_state_to_acl(&शेष_acl_state,
						flags | NFS4_ACL_TYPE_DEFAULT);
	अगर (IS_ERR(*dpacl)) अणु
		ret = PTR_ERR(*dpacl);
		*dpacl = शून्य;
		posix_acl_release(*pacl);
		*pacl = शून्य;
		जाओ out_dstate;
	पूर्ण
	sort_pacl(*pacl);
	sort_pacl(*dpacl);
	ret = 0;
out_dstate:
	मुक्त_state(&शेष_acl_state);
out_estate:
	मुक्त_state(&effective_acl_state);
	वापस ret;
पूर्ण

__be32
nfsd4_set_nfs4_acl(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp,
		काष्ठा nfs4_acl *acl)
अणु
	__be32 error;
	पूर्णांक host_error;
	काष्ठा dentry *dentry;
	काष्ठा inode *inode;
	काष्ठा posix_acl *pacl = शून्य, *dpacl = शून्य;
	अचिन्हित पूर्णांक flags = 0;

	/* Get inode */
	error = fh_verअगरy(rqstp, fhp, 0, NFSD_MAY_SATTR);
	अगर (error)
		वापस error;

	dentry = fhp->fh_dentry;
	inode = d_inode(dentry);

	अगर (S_ISसूची(inode->i_mode))
		flags = NFS4_ACL_सूची;

	host_error = nfs4_acl_nfsv4_to_posix(acl, &pacl, &dpacl, flags);
	अगर (host_error == -EINVAL)
		वापस nfserr_attrnotsupp;
	अगर (host_error < 0)
		जाओ out_nfserr;

	fh_lock(fhp);

	host_error = set_posix_acl(&init_user_ns, inode, ACL_TYPE_ACCESS, pacl);
	अगर (host_error < 0)
		जाओ out_drop_lock;

	अगर (S_ISसूची(inode->i_mode)) अणु
		host_error = set_posix_acl(&init_user_ns, inode,
					   ACL_TYPE_DEFAULT, dpacl);
	पूर्ण

out_drop_lock:
	fh_unlock(fhp);

	posix_acl_release(pacl);
	posix_acl_release(dpacl);
out_nfserr:
	अगर (host_error == -EOPNOTSUPP)
		वापस nfserr_attrnotsupp;
	अन्यथा
		वापस nfsत्रुटि_सं(host_error);
पूर्ण


अटल लघु
ace2type(काष्ठा nfs4_ace *ace)
अणु
	चयन (ace->whotype) अणु
		हाल NFS4_ACL_WHO_NAMED:
			वापस (ace->flag & NFS4_ACE_IDENTIFIER_GROUP ?
					ACL_GROUP : ACL_USER);
		हाल NFS4_ACL_WHO_OWNER:
			वापस ACL_USER_OBJ;
		हाल NFS4_ACL_WHO_GROUP:
			वापस ACL_GROUP_OBJ;
		हाल NFS4_ACL_WHO_EVERYONE:
			वापस ACL_OTHER;
	पूर्ण
	BUG();
	वापस -1;
पूर्ण

/*
 * वापस the size of the काष्ठा nfs4_acl required to represent an acl
 * with @entries entries.
 */
पूर्णांक nfs4_acl_bytes(पूर्णांक entries)
अणु
	वापस माप(काष्ठा nfs4_acl) + entries * माप(काष्ठा nfs4_ace);
पूर्ण

अटल काष्ठा अणु
	अक्षर *string;
	पूर्णांक   stringlen;
	पूर्णांक type;
पूर्ण s2t_map[] = अणु
	अणु
		.string    = "OWNER@",
		.stringlen = माप("OWNER@") - 1,
		.type      = NFS4_ACL_WHO_OWNER,
	पूर्ण,
	अणु
		.string    = "GROUP@",
		.stringlen = माप("GROUP@") - 1,
		.type      = NFS4_ACL_WHO_GROUP,
	पूर्ण,
	अणु
		.string    = "EVERYONE@",
		.stringlen = माप("EVERYONE@") - 1,
		.type      = NFS4_ACL_WHO_EVERYONE,
	पूर्ण,
पूर्ण;

पूर्णांक
nfs4_acl_get_whotype(अक्षर *p, u32 len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(s2t_map); i++) अणु
		अगर (s2t_map[i].stringlen == len &&
				0 == स_भेद(s2t_map[i].string, p, len))
			वापस s2t_map[i].type;
	पूर्ण
	वापस NFS4_ACL_WHO_NAMED;
पूर्ण

__be32 nfs4_acl_ग_लिखो_who(काष्ठा xdr_stream *xdr, पूर्णांक who)
अणु
	__be32 *p;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(s2t_map); i++) अणु
		अगर (s2t_map[i].type != who)
			जारी;
		p = xdr_reserve_space(xdr, s2t_map[i].stringlen + 4);
		अगर (!p)
			वापस nfserr_resource;
		p = xdr_encode_opaque(p, s2t_map[i].string,
					s2t_map[i].stringlen);
		वापस 0;
	पूर्ण
	WARN_ON_ONCE(1);
	वापस nfserr_serverfault;
पूर्ण
