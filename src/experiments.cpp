#include "chess.hpp"
#include <chrono>
#include <iostream>

#include "engine.hpp"
#include "evaluation.hpp"

/**
 * 100 middlegame puzzle FENs scraped from https://database.lichess.org
 */
std::vector boards = {
    chess::Board("r6k/pp2r2p/4Rp1Q/3p4/8/1N1P2R1/PqP2bPP/7K b - - 0 24"),
    chess::Board("r2qr1k1/b1p2ppp/pp4n1/P1P1p3/4P1n1/B2P2Pb/3NBP1P/RN1QR1K1 b - - 1 16"),
    chess::Board("r4rk1/pp3ppp/2n1b3/q1pp2B1/8/P1Q2NP1/1PP1PP1P/2KR3R w - - 0 15"),
    chess::Board("r1bqk2r/pp1nbNp1/2p1p2p/8/2BP4/1PN3P1/P3QP1P/3R1RK1 b kq - 0 19"),
    chess::Board("3r3r/pQNk1ppp/1qnb1n2/1B6/8/8/PPP3PP/3R1R1K w - - 5 19"),
    chess::Board("5r1k/5rp1/p7/1b2B2p/1P1P1Pq1/2R1Q3/P3p1P1/2R3K1 w - - 0 41"),
    chess::Board("r2q1rk1/5ppp/1np5/p1b5/2p1B3/P7/1P3PPP/R1BQ1RK1 b - - 1 17"),
    chess::Board("r2qk2r/pp2ppbp/1n1p2p1/3Pn3/2P5/2NBBP1P/PP3P2/R2QK2R b KQkq - 0 12"),
    chess::Board("2R2r1k/pQ4pp/5rp1/3B4/q2n4/7P/P4PP1/5RK1 w - - 3 30"),
    chess::Board("6Qk/p1p3pp/4N3/1p6/2q1r1n1/2B5/PP4PP/3R1R1K b - - 0 28"),
    chess::Board("1qr2rk1/pb2bppp/8/8/2p1N3/P1Bn2P1/2Q2PBP/1R3RK1 b - - 3 23"),
    chess::Board("r6r/1pNk1ppp/2np4/b3p3/4P1b1/N1Q5/P4PPP/R3KB1R w KQ - 3 18"),
    chess::Board("2r3k1/2r4p/4p1p1/1p1q1pP1/p1bP1P1Q/P6R/5B2/2R3K1 b - - 5 34"),
    chess::Board("5r1k/pp4pp/5p2/1BbQp1r1/6K1/7P/1PP3P1/3R3R w - - 2 26"),
    chess::Board("r4rk1/pp3ppp/3b4/2p1pPB1/7N/2PP3n/PP4PP/R2Q1RqK w - - 5 18"),
    chess::Board("2r3k1/p1q2pp1/Q3p2p/b1Np4/2nP1P2/4P1P1/5K1P/2B1N3 b - - 3 33"),
    chess::Board("6k1/1p3pp1/1p5p/2r1p3/2n5/r3PN2/2RnNPPP/2R3K1 b - - 1 32"),
    chess::Board("1rb2rk1/q5P1/4p2p/3p3p/3P1P2/2P5/2QK3P/3R2R1 b - - 0 29"),
    chess::Board("r3k2r/pb1p1ppp/1b4q1/1Q2P3/8/2NP1Pn1/PP4PP/R1B2R1K w kq - 1 17"),
    chess::Board("r4rk1/p3ppbp/Pp1q1np1/3PpbB1/2B5/2N5/1PPQ1PPP/3RR1K1 w - - 4 18"),
    chess::Board("k1r1b3/p1r1nppp/1p1qpn2/2Np4/1P1P4/PQRBPN2/5PPP/2R3K1 w - - 0 19"),
    chess::Board("r3brk1/5pp1/p1nqpn1p/P2pN3/2pP4/2P1PN2/5PPP/RB1QK2R b KQ - 4 16"),
    chess::Board("r3kb1r/ppq2ppp/4pn2/2Ppn3/1P4bP/2P2N2/P3BPP1/RNBQ1RK1 b kq - 2 10"),
    chess::Board("3r1rk1/1b1n1pp1/3p4/p4PPQ/4P3/3q1BN1/8/2R2RK1 b - - 1 28"),
    chess::Board("r3qrk1/2p2pp1/p2bpn1p/2ppNb2/3P1P2/1PP1P1B1/P2N2PP/R2Q1RK1 b - - 0 14"),
    chess::Board("7k/p4R1p/3p3r/2pN1n2/2PbBBb1/3P2P1/P3r3/5R1K w - - 1 28"),
    chess::Board("r4rk1/pp3ppp/3p1q2/P1P1p3/2B5/2B2n2/2P2P1P/R2Q1RK1 w - - 0 16"),
    chess::Board("r2q4/pp1n1kbp/3P2b1/6N1/6Q1/P3P3/6P1/4K2R b K - 1 21"),
    chess::Board("r3nrk1/1b3pp1/4pb2/p3q3/1p1N4/3B2R1/PPPQN2P/1K4R1 b - - 1 23"),
    chess::Board("r1bqr1k1/pp1nbpp1/2p2n2/6P1/2BP4/P7/1PQNNPP1/R3K2R b KQ - 0 13"),
    chess::Board("r6k/q1pb1p1p/1b3Pr1/p1ppP2Q/3P2p1/4B3/PP2NRPP/3R2K1 b - - 1 25"),
    chess::Board("r2r2k1/1p2qppp/2n1p3/5n2/p2P4/P2Q1N2/BP3PPP/2R1R1K1 w - - 4 20"),
    chess::Board("6k1/5ppp/5nb1/pp6/6rP/5N1Q/Pq2r1P1/3R2RK b - - 4 32"),
    chess::Board("2r2rk1/5ppp/bq2p3/p1ppP1N1/Pb1P2P1/1P2P2P/2QN4/2R1K2R b K - 1 18"),
    chess::Board("6k1/3bqr1p/2rpp1pR/p7/Pp1QP3/1B3P2/1PP3P1/2KR4 w - - 6 22"),
    chess::Board("r4k1r/pNqnppb1/6pn/2p3Np/7P/2P2Q2/PP3PP1/R1B1K2R b KQ - 2 15"),
    chess::Board("r4rk1/1pp2ppp/p2p4/2bPp3/2P1Pn1q/P1N2B2/1P3P2/R1BQK1R1 w Q - 1 15"),
    chess::Board("8/r1b1q2k/2p3p1/2Pp4/1P2p1n1/2B1P3/NQ6/2K4R b - - 1 36"),
    chess::Board("rn3rk1/p5pp/3N4/4np1q/5Q2/1P3K2/PB1P2P1/2R4R w - - 0 25"),
    chess::Board("r3kb1r/p4ppp/b1p1p3/3q4/3Q4/4BN2/PPP2PPP/R3K2R b KQkq - 0 11"),
    chess::Board("r1b1k2N/ppp3pp/2n5/2bp4/7q/1B4n1/PPPP1P1P/RNBQ1RK1 w q - 0 10"),
    chess::Board("r4k1r/1pp2p2/p2p3p/3N4/3P2q1/8/PPP5/1K2Q1NR b - - 1 23"),
    chess::Board("6rk/pp6/2n5/3ppn1p/3p4/2P2P1q/PP3QNB/R4R1K w - - 2 29"),
    chess::Board("r2qr1k1/ppp2ppp/4b3/3P4/1nP2Q2/2N2N1P/PP3KP1/R4R2 w - - 1 15"),
    chess::Board("2r2rk1/6pp/3Q1q2/8/3N1B2/6P1/PP1K3P/R4b2 w - - 0 24"),
    chess::Board("3r2k1/4nppp/pq1p1b2/1p2P3/2r2P2/2P1NR2/PP1Q2BP/3R2K1 b - - 0 24"),
    chess::Board("r1bk2r1/ppq2pQp/3bpn2/1BpnN3/5P2/1P6/PBPP2PP/RN2K2R w KQ - 3 13"),
    chess::Board("2kr2r1/1bp4n/1pq1p2p/p1P5/1P3B2/P6P/5RP1/RB2Q1K1 w - - 3 26"),
    chess::Board("r1bqk2r/p3Bppp/3p4/1ppn4/4P3/4Q3/PPP2PPP/2KR1B1R b kq - 0 11"),
    chess::Board("r6k/1b3pp1/p1q1pn1p/2p5/P1B5/1PN4Q/2P1RP1P/R4Kr1 w - - 2 26"),
    chess::Board("r4rk1/3q1pbp/p1n1p1p1/2p3NP/1p3B2/3P3Q/PPP3P1/R3R1K1 b - - 2 19"),
    chess::Board("r2r2k1/2q1bpp1/3p1n1p/1ppN4/1P1BP3/P5Q1/4RPPP/R5K1 b - - 1 20"),
    chess::Board("4rr1k/pQpn2pp/3p1q2/8/8/2P5/PP3PPP/RN3RK1 w - - 1 16"),
    chess::Board("3q2k1/2r5/pp3p1Q/2b1n3/P3N3/2P5/1P4PP/R6K b - - 0 24"),
    chess::Board("r1b2rk1/ppq2ppp/8/4b2Q/4R3/3B4/PP3PPP/R1B3K1 b - - 1 15"),
    chess::Board("r1b2rk1/p3pp2/2B4b/2Qpq3/3N2pp/4P3/2P2PPP/1R2K2R b K - 1 23"),
    chess::Board("5k2/p4pp1/1qn3r1/3pP2p/5P2/1NPQ4/Pr3RPP/R5K1 w - - 5 24"),
    chess::Board("2rr4/2N2pk1/p1Q1b1pp/1p4q1/3pP3/1B1P4/PPP3PP/6RK w - - 7 25"),
    chess::Board("3rk2r/2qn1pp1/p1Q1R3/3n3p/8/8/PP4PP/5R1K b k - 0 23"),
    chess::Board("1r6/pp2kpp1/2n1p1n1/3p2PQ/5P2/2PqP3/PP1N4/2KR3R w - - 3 27"),
    chess::Board("r1b1kb1Q/ppp4p/6pB/3P4/2pn4/8/PPP1qPPP/RN1K3R w q - 2 13"),
    chess::Board("r1r3k1/ppq3bQ/4p2p/4n3/3p4/2P5/PBB2PPP/4R1K1 b - - 2 24"),
    chess::Board("7r/ppp2kp1/2nb1pp1/3p3r/3P2q1/2PQB2P/PP3PP1/R3R1K1 w - - 0 18"),
    chess::Board("r1q3k1/4bppp/pp2pn2/4B3/8/2N2Q2/PPPR1PPP/6K1 b - - 0 18"),
    chess::Board("1r6/k2qn1b1/p1b1p1p1/2PpPpN1/2nN1P1P/p4B2/1PP2Q2/1K1R3R w - - 0 32"),
    chess::Board("1k1r3r/2q5/pp1n2p1/8/1Q6/3R2P1/PPP2P1P/3R2K1 b - - 4 29"),
    chess::Board("r5kr/pp1qb1p1/2p4p/3pPb1Q/3P4/2P1B3/PP4PP/R4RK1 b - - 1 17"),
    chess::Board("3r1rk1/1p4p1/p1p3Qp/2q5/8/3n1N1P/PP1R2P1/5R1K b - - 7 28"),
    chess::Board("r1b4r/pp1k2pp/2nb2q1/1B1p2B1/3p3Q/8/PPP2PPP/3RR1K1 b - - 5 17"),
    chess::Board("r4rk1/3nqpp1/2p1bn1p/3pN3/1p1P4/2NQP2P/1PB2PP1/R4RK1 w - - 0 18"),
    chess::Board("1r4k1/4bpp1/1rp2n1p/3p4/3P4/2N1B1P1/Pq2QPKP/2R1R3 w - - 3 24"),
    chess::Board("r2qr2k/1pp2pp1/1b4np/pP2P3/P4n2/BQN2N1P/5PP1/R3R1K1 w - - 3 20"),
    chess::Board("r4r2/2q1NN2/4bQpk/2n4p/pp5P/8/1PP2PP1/2KR3R b - - 0 28"),
    chess::Board("3q1nk1/1bN2rpp/pp1P4/1N6/4n2b/8/PPP2PPP/R1BQ1RK1 w - - 1 16"),
    chess::Board("rn3bk1/2rqp2p/2p3p1/3p1p2/3P1P1B/pP1BP3/P1Q2PRP/1KR5 b - - 0 26"),
    chess::Board("rk5r/1b3R2/pp2p2q/4P2p/B2p3B/4R2P/PP4P1/5Q1K b - - 0 27"),
    chess::Board("r3kb1r/3nnpp1/4p1bp/1NppP3/3P4/6N1/P2BBPPP/R3K2R b KQkq - 0 17"),
    chess::Board("rn2q1k1/pp3ppp/2pb4/3p1B2/2Pn4/1Q3N2/PP3PPP/R1B4K w - - 0 15"),
    chess::Board("2kr3r/p1p1bpp1/2p2n1p/8/8/1P6/P1P1RPPP/RNB3K1 w - - 1 16"),
    chess::Board("2kr3r/pp1n2pp/2QB1bp1/5q2/2B5/8/PPP2PPP/3R1RK1 b - - 0 17"),
    chess::Board("rn3rk1/4pp1p/3p2pB/2q4P/3bP1b1/Pp2Q3/1P2B3/1K1R2NR w - - 0 20"),
    chess::Board("r1bq3Q/1np2kp1/p5B1/1p1Pp3/1Pn2BP1/2b2P2/P3K3/R4N2 b - - 5 35"),
    chess::Board("r3k1nr/1pp2ppp/1pnp2q1/4p1B1/2B1P3/3P1Q1P/PPP2PP1/R4RK1 b kq - 0 11"),
    chess::Board("r4rk1/2q2ppp/3pp3/4Pb1N/pp6/1B4Q1/PPP3PP/1K1RR3 b - - 0 21"),
    chess::Board("r4rk1/6p1/b3p1nN/p1pp4/1p3P1q/3P1Q1B/PPP2PK1/R6R b - - 0 26"),
    chess::Board("6k1/2p2ppp/pnp5/B7/2P3PP/1P1bPPR1/r6r/3R2K1 b - - 1 29"),
    chess::Board("r5k1/1p1rqpp1/p3pnp1/2PN4/8/1Q5P/PP3PP1/3RR1K1 b - - 0 24"),
    chess::Board("r3k2r/ppp2p1p/2n1pp2/7q/2PN2b1/2BP1Pb1/PP2B1P1/R2Q1RK1 w kq - 1 16"),
    chess::Board("7k/pb1qn2n/1p2R2Q/2p2p2/2Pp4/3B4/PP3PrP/4RK2 b - - 1 27"),
    chess::Board("2rq1rk1/7p/1n4pb/1R2p3/pPpP1P2/P1B5/3NQ1PP/2R3K1 w - - 0 31"),
    chess::Board("1r3rk1/q4ppp/p3Pb2/3nN3/P2P4/7Q/1B4PP/1R3RK1 b - - 0 24"),
    chess::Board("3rk3/5p1r/p2Np1p1/3bP3/P2n4/8/1P3RPP/5RK1 b - - 4 25"),
    chess::Board("6k1/pb2r1pN/1n4Bp/3p4/1P2pR2/P7/3R1PPP/2r3K1 w - - 2 30"),
    chess::Board("r2b2k1/1p3q1p/p2p4/3P2p1/2P1PRQr/8/P2B3P/2R4K w - - 1 29"),
    chess::Board("1r3rk1/1pq2pbp/p1p1pnp1/2N1N3/3P4/1QP5/PP3PPP/3RR1K1 w - - 2 19"),
    chess::Board("rqnr2k1/5ppp/p2p4/4Q3/8/1P5P/PBP2PP1/R2R2K1 b - - 2 23"),
    chess::Board("r4k1r/pp3pp1/4p3/3pP1np/6bq/1PP2P2/P3B1PP/RN1Q1RK1 w - - 1 14"),
    chess::Board("2kr2r1/ppb2ppp/3qbn2/2Np2B1/P7/2P2Q1P/1PB2PP1/R4RK1 w - - 5 18"),
    chess::Board("2r3k1/7p/6q1/p1Np4/Qp2pr2/P4P2/1PR2P1K/5R2 w - - 0 36"),
    chess::Board("1R6/6pk/2p4p/3bP2r/5B1P/2P2qP1/P4P1Q/4R1K1 w - - 2 40"),
};

void bench()
{
    constexpr double ITERATIONS = 100;

    const auto start1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITERATIONS; i++)
    {
        evaluation::mobility_eval(boards[i]);
    }
    const auto end1 = std::chrono::high_resolution_clock::now();
    const auto time_per_split_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - start1).count() / (
        ITERATIONS * 1'000'000.0);

    std::cout << "Estimated mobility_eval cost:  " << time_per_split_ms * 23'858'041 / 1'000
        << " s" << std::endl;
}

void experiments()
{
    const auto commands =
        "position startpos moves e2e3\ngo movetime 10000\nsetoption name Ponder value true\nposition startpos moves e2e3 b8c6 b1c3\ngo wtime 60470 btime 57999 winc 1000 binc 1000\nposition startpos moves e2e3 b8c6 b1c3 e7e5 d1g4\ngo wtime 61290 btime 55489 winc 1000 binc 1000\nposition startpos moves e2e3 b8c6 b1c3 e7e5 d1g4 g8f6 g4c4\ngo wtime 62100 btime 53109 winc 1000 binc 1000\nposition startpos moves e2e3 b8c6 b1c3 e7e5 d1g4 g8f6 g4c4 d7d5 c4a4\ngo wtime 62910 btime 50849 winc 1000 binc 1000\nposition startpos moves e2e3 b8c6 b1c3 e7e5 d1g4 g8f6 g4c4 d7d5 c4a4 d5d4 c3d1\ngo wtime 63710 btime 48699 winc 1000 binc 1000\nposition startpos moves e2e3 b8c6 b1c3 e7e5 d1g4 g8f6 g4c4 d7d5 c4a4 d5d4 c3d1 f8c5 g1f3\ngo wtime 64520 btime 46659 winc 1000 binc 1000\nposition startpos moves e2e3 b8c6 b1c3 e7e5 d1g4 g8f6 g4c4 d7d5 c4a4 d5d4 c3d1 f8c5 g1f3 e8g8 b2b3\ngo wtime 65330 btime 44719 winc 1000 binc 1000\nposition startpos moves e2e3 b8c6 b1c3 e7e5 d1g4 g8f6 g4c4 d7d5 c4a4 d5d4 c3d1 f8c5 g1f3 e8g8 b2b3 c6b4 c2c3\ngo wtime 66130 btime 42879 winc 1000 binc 1000\nposition startpos moves e2e3 b8c6 b1c3 e7e5 d1g4 g8f6 g4c4 d7d5 c4a4 d5d4 c3d1 f8c5 g1f3 e8g8 b2b3 c6b4 c2c3 b4c2 e1e2\ngo wtime 66950 btime 41129 winc 1000 binc 1000";
    auto input = std::istringstream(commands);
    auto output = std::ostringstream();
    engine::start_uci(input, output);
    std::cout << "Engine output (best moves): " << std::endl;
    std::cout << output.str() << std::endl;
    std::cout << "EXPECTED ON LAST LINE: d4d3" << std::endl;

}

void test()
{
    auto table = TranspositionTable();
    auto board = chess::Board("8/5ppp/4n3/R3k3/6P1/2r4P/5PK1/8 b - - 15 49");
    const auto result = engine::negamax(chess::Move::NO_MOVE, table, board,
                                        engine::initial_alpha, engine::initial_beta,
                                        chess::Move::NO_MOVE, 1, 0);
    std::cout << chess::uci::moveToUci(std::get<1>(result)) << std::endl;
    // std::cout << "NULL_MOVE (UCI representation): " << chess::uci::moveToUci(chess::Move::NULL_MOVE) << std::endl;
    // std::cout << "NO_MOVE (UCI representation): " << chess::uci::moveToUci(chess::Move::NO_MOVE) << std::endl;
}

int main()
{
    experiments();
    return 0;
}
