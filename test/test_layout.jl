using Test
using MESTI

@testset "MUMPS 5.9.0 struct layout" begin
    T = Mumps{ComplexF64,Float64}
    fn = fieldnames(T)

    off(f) = Int(fieldoffset(T, findfirst(==(f), fn)))

    @testset "Struct information" begin
        @info "sizeof(Mumps)" sizeof(T)

        @info "Field offsets" Dict(
            :rinfo               => off(:rinfo),
            :rinfog              => off(:rinfog),
            :pivnul_list         => off(:pivnul_list),
            :mapping             => off(:mapping),
            :singular_values     => off(:singular_values),
            :nb_singular_values  => off(:nb_singular_values),
            :size_schur          => off(:size_schur),
            :listvar_schur       => off(:listvar_schur),
            :schur               => off(:schur),
        )

        # The new MUMPS 5.9 field must exist.
        @test :nb_singular_values in fn

        # The old MUMPS 5.7 field must be gone.
        @test !(:deficiency in fn)
    end

    @testset "Relative layout" begin
        @test off(:mapping)              - off(:pivnul_list)        == 8
        @test off(:singular_values)      - off(:mapping)            == 8
        @test off(:nb_singular_values)   - off(:singular_values)    == 8
        @test off(:size_schur)           - off(:nb_singular_values) == 4
        @test off(:listvar_schur)        - off(:size_schur)         == 4
        @test off(:schur)                - off(:listvar_schur)      == 8
    end
end