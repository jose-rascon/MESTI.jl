using MESTI

T = Mumps{ComplexF64,Float64}
fn = fieldnames(T)

println("sizeof = ", sizeof(T))
println()

for f in (
    :rinfo,
    :rinfog,
    :pivnul_list,
    :mapping,
    :singular_values,
    :nb_singular_values,
    :size_schur,
    :listvar_schur,
    :schur,
)
    idx = findfirst(==(f), fn)
    println(rpad(String(f), 22),
            " index=", idx,
            " offset=", Int(fieldoffset(T, idx)))
end