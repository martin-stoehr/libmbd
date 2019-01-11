// vim: set ft=c:

extern const _Bool cmbd_with_mpi;
extern const _Bool cmbd_with_scalapack;

struct cmbd_calc {};

struct cmbd_calc* cmbd_init_calc();
void cmbd_destroy_calc(struct cmbd_calc* calc);

void cmbd_get_exception(
    struct cmbd_calc* calc,
    int* code,
    char origin[50],
    char msg[150]
);

void cmbd_toggle_muted(
    struct cmbd_calc* calc
);

struct geom_t* cmbd_init_geom(
    struct cmbd_calc* calc,
    int n_atoms,
    double* coords,
    double* lattice,
    int* k_grid,
    int n_freq
);

void cmbd_destroy_geom(struct geom_t* geom);

struct cmbd_damping* cmbd_init_damping(
    int n_atoms,
    char* version,
    double* R_vdw,
    double* sigma,
    double beta,
    double a
);

void cmbd_destroy_damping(struct cmbd_damping* damping);

double cmbd_ts_energy(
    struct geom_t* geom,
    int n_atoms,
    double* alpha_0,
    double* C6,
    struct cmbd_damping* damping
);

double cmbd_mbd_energy(
    struct geom_t* geom,
    int n_atoms,
    double* alpha_0,
    double* C6,
    struct cmbd_damping* damping,
    double* gradients,
    double* latt_gradients
);

double cmbd_rpa_energy(
    struct geom_t* geom,
    int n_atoms,
    double* alpha_0,
    double* C6,
    struct cmbd_damping* damping,
    double* gradients,
    double* latt_gradients
);

double cmbd_mbd_rsscs_energy(
    struct geom_t* geom,
    int n_atoms,
    double* alpha_0,
    double* C6,
    struct cmbd_damping* damping,
    double* gradients,
    double* latt_gradients,
    double* eigvals,
    double* eigvecs
);

double cmbd_mbd_scs_energy(
    struct geom_t* geom,
    int n_atoms,
    double* alpha_0,
    double* C6,
    struct cmbd_damping* damping,
    double* gradients,
    double* latt_gradients
);

double cmbd_dipole_matrix(
    struct geom_t* geom,
    struct cmbd_damping* damping,
    double* q_point,
    double* dipmat
);

double cmbd_coulomb_energy(
    struct geom_t* geom,
    int n_atoms,
    double* q,
    double* m,
    double* w_t,
    char* version,
    double* r_vdw,
    double beta,
    double a,
    double* C
);

double cmbd_dipole_energy(
    struct geom_t* geom,
    int n_atoms,
    double* a0,
    double* w,
    double* w_t,
    char* version,
    double* r_vdw,
    double beta,
    double a,
    double* C
);
